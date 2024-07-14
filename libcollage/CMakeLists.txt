cmake_minimum_required(VERSION 3.16)
project(collage)

set(CMAKE_CXX_STANDARD 17)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

find_package(PkgConfig)
pkg_check_modules(LIBMYSQLCLIENT REQUIRED mysqlclient)
link_directories(${LIBMYSQLCLIENT_LIBRARY_DIRS})
add_library(collage SHARED libcollage.cpp m_ctypes.h)
target_include_directories(collage PUBLIC ${LIBMYSQLCLIENT_INCLUDE_DIRS})
find_library(LIBMYSQLCLIENT_LIB NAMES libmysqlclient.a)
target_link_libraries(collage ${LIBMYSQLCLIENT_LIB} -lzstd -lz -lssl -lcrypto -lresolv -lm)

if (APPLE)
    add_custom_command(TARGET collage POST_BUILD
            COMMAND libtool -static -o collage.a $<TARGET_FILE:collage> ${LIBMYSQLCLIENT_LIB} DEPENDS collage)
else ()
    add_custom_command(TARGET collage POST_BUILD
            COMMAND ar crsT collage.a $<TARGET_FILE:collage> ${LIBMYSQLCLIENT_LIB} DEPENDS collage)
endif ()
add_executable(main main.cpp)
target_link_libraries(main collage)
