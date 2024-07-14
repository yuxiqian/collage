#include <jni.h>
#include <mysql.h>

#include <iostream>
#include <tuple>

#include "libcollage.h"
#include "m_ctypes.h"

namespace LibCollage {
std::tuple<const char *, size_t> get_span(const std::string &str) {
    return {str.c_str(), str.size()};
}

int compare(const char *charset, const std::string &lhs,
            const std::string &rhs) {
    auto [lhs_bytes, lhs_size] = get_span(lhs);
    auto [rhs_bytes, rhs_size] = get_span(rhs);
    return compare(charset, lhs_bytes, lhs_size, rhs_bytes, rhs_size);
}

int compare(const char *charset, const jbyte *lhs, const size_t lhs_size,
            const jbyte *rhs, const size_t rhs_size) {
    return compare(charset, reinterpret_cast<const char *>(lhs), lhs_size,
                   reinterpret_cast<const char *>(rhs), rhs_size);
}

int compare(const char *charset, const char *lhs, const size_t lhs_size,
            const char *rhs, const size_t rhs_size) {
    if (MYSQL *mysql = mysql_init(nullptr);
        !mysql_set_character_set(mysql, charset)) {
        const CHARSET_INFO *charset_info = mysql->charset;
        return charset_info->coll->strnncollsp(
            charset_info, reinterpret_cast<const uint8_t *>(lhs), lhs_size,
            reinterpret_cast<const uint8_t *>(rhs), rhs_size);
    }
    throw std::runtime_error("unknown charset: " + std::string(charset));
}

extern "C" JNIEXPORT jint JNICALL
Java_io_github_yuxiqian_libcollage_Collation_compare(JNIEnv *env, jobject,
                                                     jstring j_charset,
                                                     jstring j_lhs,
                                                     jstring j_rhs) {
    const char *charset = env->GetStringUTFChars(j_charset, nullptr);
    const char *lhs = env->GetStringUTFChars(j_lhs, nullptr);
    const auto lhs_size = static_cast<uint8_t>(env->GetStringUTFLength(j_lhs));
    const char *rhs = env->GetStringUTFChars(j_rhs, nullptr);
    const auto rhs_size = static_cast<uint8_t>(env->GetStringUTFLength(j_rhs));
    jint ret;
    bool success = true;
    try {
        ret = compare(charset, lhs, lhs_size, rhs, rhs_size);
    } catch (std::runtime_error &e) {
        success = false;
    }
    env->ReleaseStringUTFChars(j_lhs, lhs);
    env->ReleaseStringUTFChars(j_rhs, rhs);
    if (!success) {
        env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"),
                      "Failed to compare");
    }
    return ret;
}

extern "C" JNIEXPORT jint JNICALL
Java_io_github_yuxiqian_libcollage_Collation_compareBytes(JNIEnv *env, jobject,
                                                          jstring j_charset,
                                                          jbyteArray j_lhs,
                                                          jbyteArray j_rhs) {
    const char *charset = env->GetStringUTFChars(j_charset, nullptr);
    jbyte *lhs = env->GetByteArrayElements(j_lhs, nullptr);
    const auto lhs_size = static_cast<uint8_t>(env->GetArrayLength(j_lhs));
    jbyte *rhs = env->GetByteArrayElements(j_rhs, nullptr);
    const auto rhs_size = static_cast<uint8_t>(env->GetArrayLength(j_rhs));
    jint ret;
    bool success = true;
    try {
        ret = compare(charset, lhs, lhs_size, rhs, rhs_size);
    } catch (std::runtime_error &e) {
        success = false;
    }
    env->ReleaseByteArrayElements(j_lhs, lhs, JNI_ABORT);
    env->ReleaseByteArrayElements(j_rhs, rhs, JNI_ABORT);
    if (!success) {
        env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"),
                      "Failed to compare bytes");
    }
    return ret;
}
}  // namespace LibCollage