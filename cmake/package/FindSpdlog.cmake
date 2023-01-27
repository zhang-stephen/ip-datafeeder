# ** EXPERIMENTAL **
# TRY to find spdlog installed from homebrew
# Assumptions:
#   - Release only
#   - PkgConfig is available
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

find_package(PkgConfig)
include(FindPackageHandleStandardArgs)

set(SPDLOG_PACKAGE_NAME spdlog)

pkg_check_modules(PC_${SPDLOG_PACKAGE_NAME} QUIET ${SPDLOG_PACKAGE_NAME})

find_path(
    ${SPDLOG_PACKAGE_NAME}_INCLUDE_DIR
    NAME spdlog/spdlog.h
    PATHS ${PC_spdlog_INCLUDE_DIRS}
    PATH_SUFFIXES ${SPDLOG_PACKAGE_NAME}
)

find_library(
    ${SPDLOG_PACKAGE_NAME}_LIBRARY
    NAME ${SPDLOG_PACKAGE_NAME}
    PATHS ${PC_spdlog_LIBRARY_DIRS}
)

set(${SPDLOG_PACKAGE_NAME}_VERSION ${PC_spdlog_VERSION})

find_package_handle_standard_args(
    ${SPDLOG_PACKAGE_NAME}
    FOUND_VAR
        ${SPDLOG_PACKAGE_NAME}_FOUND
    REQUIRED_VARS
        ${SPDLOG_PACKAGE_NAME}_LIBRARY
        ${SPDLOG_PACKAGE_NAME}_INCLUDE_DIR
    VERSION_VAR
        ${SPDLOG_PACKAGE_NAME}_VERSION
)

# EOF
