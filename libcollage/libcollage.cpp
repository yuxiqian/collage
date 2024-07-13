#include "libcollage.h"
#include <iostream>
#include <tuple>
#include <jni.h>
#include <mysql.h>
#include "m_ctypes.h"

namespace LibCollage {
    std::tuple<const uint8_t *, size_t> get_span(const std::string &str) {
        return {reinterpret_cast<const uint8_t *>(str.c_str()), str.size()};
    }

    int compare(const char *charset, const std::string &lhs, const std::string &rhs) {
        auto [lhs_bytes, lhs_size] = get_span(lhs);
        auto [rhs_bytes, rhs_size] = get_span(rhs);
        return compare(charset, lhs_bytes, lhs_size, rhs_bytes, rhs_size);
    }

    int compare(const char *charset, const uint8_t *lhs, const size_t lhs_size, const uint8_t *rhs, const size_t rhs_size) {
        if (MYSQL *mysql = mysql_init(nullptr); !mysql_set_character_set(mysql, charset)) {
            const CHARSET_INFO *charset_info = mysql->charset;
            return charset_info->coll->strnncollsp(charset_info, lhs, lhs_size, rhs, rhs_size);
        }
        throw std::runtime_error("unknown charset: " + std::string(charset));
    }

    extern "C" JNIEXPORT jint JNICALL Java_io_github_yuxiqian_libcollage_Collation_compare(
        JNIEnv *env, jobject, jstring j_charset, jstring j_lhs, jstring j_rhs) {
        const char *charset = env->GetStringUTFChars(j_charset, nullptr);
        const auto lhs = reinterpret_cast<const uint8_t *>(env->GetStringUTFChars(j_lhs, nullptr));
        const auto lhs_size = static_cast<uint8_t>(env->GetStringUTFLength(j_lhs));
        const auto rhs = reinterpret_cast<const uint8_t *>(env->GetStringUTFChars(j_rhs, nullptr));
        const auto rhs_size = static_cast<uint8_t>(env->GetStringUTFLength(j_rhs));
        try {
            return compare(charset, lhs, lhs_size, rhs, rhs_size);
        } catch (std::runtime_error &e) {
            env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"), e.what());
        }
    }
}