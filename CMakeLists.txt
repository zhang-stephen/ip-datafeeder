# IP-Datafeeder Building
# The prototype is build on Macbook M1 Pro, and more platform will be supported soon.
# planning:
#   - Windows 10/11 x86_64(MSYS2/MSVC)
#   - Ubuntu 22.04 LTS x86_64
#   - Mac OS 13 aarch64
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

cmake_minimum_required(VERSION 3.23)

project(
    IP_DATAFEEDER
    LANGUAGES CXX # C
    DESCRIPTION "A LAN datafeeder, for embeded/FPGA debugging"
)

# includes
include(cmake/options.cmake)
include(cmake/common.cmake)
include(cmake/commands.cmake)
include(CTest)

# find_package(PkgConfig REQUIRED)
find_package(spdlog 1.11.0 CONFIG REQUIRED)
find_package(fmt 9.1.0 CONFIG REQUIRED)
find_package(GTest 1.12.0 CONFIG REQUIRED)

configure_file(src/Config.hh.in ${CMAKE_BINARY_DIR}/Config.hh)

add_subdirectory(src)  # source files
add_subdirectory(test) # UT/MT/Others

# EOF
