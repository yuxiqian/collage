#ifndef LIBCOLLAGE_H
#define LIBCOLLAGE_H
#include <jni.h>

#include <string>
#include <cstddef>

namespace LibCollage {
    int compare(const char *collation_name, const std::string &lhs,
                const std::string &rhs);

    int compare(const char *collation_name, const jbyte *lhs, size_t lhs_size,
                const jbyte *rhs, size_t rhs_size);

    int compare(const char *collation_name, const char *, size_t, const char *, size_t);

    extern "C" JNIEXPORT jint JNICALL
    Java_io_github_yuxiqian_libcollage_Collation_compareBytes(JNIEnv *env, jobject,
                                                              jstring j_col_name,
                                                              jbyteArray j_lhs,
                                                              jbyteArray j_rhs);
} // namespace LibCollage

#endif  // LIBCOLLAGE_H
