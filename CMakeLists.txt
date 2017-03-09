cmake_minimum_required(VERSION 3.6)
project(concube)

set(CMAKE_C_STANDARD 99)

find_package(LibXml2)
include_directories(${LIBXML2_INCLUDE_DIR})


set(SOURCE_FILES concube.c converter.c)
add_executable(concube ${SOURCE_FILES})