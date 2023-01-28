# ** EXPERIMENTAL **
# TRY to find fmtlib installed from homebrew
# STL format is not supported completely in LLVM 15
# Assumptions:
#   - Release only
#   - PkgConfig is available
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

include(FindPackageHandleStandardArgs)

set(FMT_PACKAGE_NAME fmt)

pkg_check_modules(PC_${FMT_PACKAGE_NAME} QUIET ${FMT_PACKAGE_NAME})

find_path(
    ${FMT_PACKAGE_NAME}_INCLUDE_DIR
    NAME fmt/format.h
    PATHS ${PC_fmt_INCLUDE_DIRS}
    PATH_SUFFIXES ${FMT_PACKAGE_NAME}
)

find_library(
    ${FMT_PACKAGE_NAME}_LIBRARY
    NAME ${FMT_PACKAGE_NAME}
    PATHS ${PC_fmt_LIBRARY_DIRS}
)

set(${FMT_PACKAGE_NAME}_VERSION ${PC_fmt_VERSION})

find_package_handle_standard_args(
    ${FMT_PACKAGE_NAME}
    FOUND_VAR
        ${FMT_PACKAGE_NAME}_FOUND
    REQUIRED_VARS
        ${FMT_PACKAGE_NAME}_LIBRARY
        ${FMT_PACKAGE_NAME}_INCLUDE_DIR
    VERSION_VAR
        ${FMT_PACKAGE_NAME}_VERSION
)

# EOF
