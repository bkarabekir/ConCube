cmake_minimum_required(VERSION 3.6)
project(concube)

set(CMAKE_C_STANDARD 11)

find_package(LibXml2)
include_directories(${LIBXML2_INCLUDE_DIR})

include_directories(/opt/local/include)


set(SOURCE_FILES concube.c fromxml.c fromxml.h fromjson.c fromjson.h fromcsv.c fromcsv.h message.h debug.h)
add_executable(concube ${SOURCE_FILES})