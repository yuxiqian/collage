cmake_minimum_required(VERSION 3.29)
project(collage)

set(CMAKE_CXX_STANDARD 17)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

find_package(PkgConfig)
pkg_check_modules(LIBMYSQLCLIENT REQUIRED mysqlclient>=8.0)

link_directories(${LIBMYSQLCLIENT_LIBRARY_DIRS})
add_library(collage SHARED libcollage.cpp m_ctypes.h)
target_include_directories(collage PUBLIC ${LIBMYSQLCLIENT_INCLUDE_DIRS})
target_link_libraries(collage PRIVATE ${LIBMYSQLCLIENT_LIBRARIES})

add_executable(main main.cpp)
target_link_libraries(main collage)
