#include <jni.h>
#include <mysql.h>

#include <iostream>
#include <tuple>
#include "libcollage.h"
#include "m_ctypes.h"

extern CHARSET_INFO *get_charset_by_name(const char *cs_name, myf flags);

namespace LibCollage {
    static MYSQL *mysql = mysql_init(nullptr);

    std::tuple<const char *, size_t> get_span(const std::string &str) {
        return {str.c_str(), str.size()};
    }

    int compare(const char *collation_name, const std::string &lhs,
                const std::string &rhs) {
        auto [lhs_bytes, lhs_size] = get_span(lhs);
        auto [rhs_bytes, rhs_size] = get_span(rhs);
        return compare(collation_name, lhs_bytes, lhs_size, rhs_bytes, rhs_size);
    }

    int compare(const char *collation_name, const jbyte *lhs, size_t lhs_size,
                const jbyte *rhs, size_t rhs_size) {
        return compare(collation_name, reinterpret_cast<const char *>(lhs), lhs_size,
                       reinterpret_cast<const char *>(rhs), rhs_size);
    }

    int compare(const char *collation_name, const char *lhs, size_t lhs_size,
                const char *rhs, size_t rhs_size) {
        const CHARSET_INFO *charset_info = get_charset_by_name(collation_name, 0);
        if (charset_info == nullptr) {
            throw std::runtime_error("unknown collation name: " + std::string(collation_name));
        }
        return charset_info->coll->strnncollsp(
            charset_info, reinterpret_cast<const uint8_t *>(lhs), lhs_size,
            reinterpret_cast<const uint8_t *>(rhs), rhs_size);
    }

    extern "C" JNIEXPORT jint JNICALL
    Java_io_github_yuxiqian_libcollage_Collation_compareBytes(JNIEnv *env, jobject,
                                                              jstring j_col_name,
                                                              jbyteArray j_lhs,
                                                              jbyteArray j_rhs) {
        const char *charset = env->GetStringUTFChars(j_col_name, nullptr);
        jbyte *lhs = env->GetByteArrayElements(j_lhs, nullptr);
        const auto lhs_size = static_cast<uint8_t>(env->GetArrayLength(j_lhs));
        jbyte *rhs = env->GetByteArrayElements(j_rhs, nullptr);
        const auto rhs_size = static_cast<uint8_t>(env->GetArrayLength(j_rhs));
        jint ret = 0;
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
} // namespace LibCollage
