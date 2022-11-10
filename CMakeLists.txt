# The Main Entrypoint of ip-datafeeder building, cmake 3.20+ is required
# Target: Windows 10/11 x86_64
# Language: C++20
# Compiler: GCC
# Author: Stephen Zhang
# Date: 2022-11-10

cmake_minimum_required(VERSION 3.20)
project(ip_datafeeder)

# Add cmake modules and includes
list(
    APPEND
    CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
)

include(compiler)
include(options)

# subdirectories
add_subdirectory(
    ${PROJECT_SOURCE_DIR}/src
)

# others
add_executable(debug main.cc)

target_link_libraries(
    debug
    PUBLIC
        compiler_conf
)

# EOF