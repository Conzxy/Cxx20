cmake_minimum_required(VERSION 3.24)
project(CXX20_demo)

include(cmake/exe_util.cmake)

# add_executable_20(format format.cpp)

file(GLOB DEMO_FILES
    ./*.cc
    concurrency/*.cc
    concept/*.cc
    constexpr/*.cc
    ranges/*.cc
)

add_single_file_executable(DEMO_FILES)
include_directories(.)