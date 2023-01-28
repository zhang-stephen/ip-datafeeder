# IP-Datafeeder Building
# The prototype is build on Macbook M1 Pro, and more platform will be supported soon.
# planning:
#   - Windows 10/11 x86_64(MSYS2/MSVC)
#   - Ubuntu 22.04 LTS x86_64
#   - Mac OS 13 aarch64
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

cmake_minimum_required(VERSION 3.18)

# includes
include(cmake/options.cmake)
include(cmake/common.cmake)

project(
    IP_DATAFEEDER
    LANGUAGES CXX # C
    DESCRIPTION "A LAN datafeeder, for embeded/FPGA debugging"
)

find_package(PkgConfig REQUIRED)
find_package(spdlog 1.11.0 REQUIRED)
find_package(fmt 9.1.0 REQUIRED)
find_package(GTest 1.13.0 REQUIRED)

add_subdirectory(src)  # source files
# add_subdirectory(test) # UT/MT/Others

# EOF
