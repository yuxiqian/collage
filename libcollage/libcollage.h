#ifndef LIBCOLLAGE_H
#define LIBCOLLAGE_H
#include <jni.h>

#include <cstddef>
#include <cstdint>
#include <string>

namespace LibCollage {
    int compare(const char *charset, const std::string &lhs,
                const std::string &rhs);
    int compare(const char *charset, const jbyte *lhs, const size_t lhs_size,
                const jbyte *rhs, const size_t rhs_size);
    int compare(const char *, const char *, size_t, const char *, size_t);

    extern "C" JNIEXPORT jint JNICALL
    Java_io_github_yuxiqian_libcollage_Collation_compare(JNIEnv *env, jobject thiz,
                                                         jstring charset,
                                                         jstring lhs, jstring rhs);
}  // namespace LibCollage

#endif  // LIBCOLLAGE_H
