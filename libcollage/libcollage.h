#ifndef LIBCOLLAGE_H
#define LIBCOLLAGE_H
#include <cstdint>
#include <cstddef>
#include <string>
#include <jni.h>

namespace LibCollage {
    int compare(const char *charset, const std::string& lhs, const std::string& rhs);
    int compare(const char *, const uint8_t *, size_t, const uint8_t *, size_t);

    extern "C" JNIEXPORT jint JNICALL Java_io_github_yuxiqian_libcollage_Collation_compare(
        JNIEnv *env, jobject thiz, jstring charset, jstring lhs, jstring rhs);
}

#endif //LIBCOLLAGE_H
