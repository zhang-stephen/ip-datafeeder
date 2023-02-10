# the common configuration for cmake
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

# configurations for cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS true)         # generate compile_commands.json automatically
set(CMAKE_CXX_STANDARD 20)                      # C++20/C17(if needed)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)
list(APPEND CMAKE_MODULE_PATH cmake/package)    # find_package in module mode

# variables
# NOTE: variables with lower-case are private.
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# configurations for compilers(llvm/gnu)
add_library(compiler INTERFACE)

if(USE_BREW_LLVM)
    set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
    # set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
    target_include_directories(
        compiler
        INTERFACE
            /opt/homebrew/opt/llvm/include
    )
    target_link_directories(
        compiler
        INTERFACE
            /opt/homebrew/opt/llvm/lib
            /opt/homebrew/opt/llvm/lib/c++
    )
    target_compile_options(
        compiler
        INTERFACE
            # linker input unused
            # -Wl,-rpath,/opt/homebrew/opt/llvm/lib/c++
    )
endif()

target_compile_options(
    compiler
    INTERFACE
        # BUILD_INTERFACE: options effective for this repo only.
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
        # FIXME: MSVC is not supported now.
        # "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# platform
if (CMAKE_HOST_APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
elseif (CMAKE_HOST_WIN32)
    if (USE_MSVC)
        set(VCPKG_TARGET_TRIPLET x64-windows)
    else()
        set(VCPKG_TARGET_TRIPLET x64-mingw-static)
    endif()
    message(STATUS "vcpkg triplet: ${VCPKG_TARGET_TRIPLET}")
endif()

# EOF
