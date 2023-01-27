# User Options for ip-datafeeder building
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

# common options
## Dependencies
option(
    USE_SYSTEM_GTEST
    "Use GoogleTest provided by system, instead of git submodule"
    true
)

option(
    USE_SYSTEM_SPDLOG
    "Use spdlog provided by system, instead of git submodule"
    false
)

# platform specific options
if(CMAKE_HOST_APPLE)
    # for MacOS
    option(
        USE_BREW_LLVM
        "Use LLVM from homebrew instead of system. MacOS only"
        true
    )
elseif(${CMAKE_HOST_LINUX})
    # for Linux distros
elseif(${CMAKE_HOST_WIN32})
    # for MS Windows
endif()

# EOF
