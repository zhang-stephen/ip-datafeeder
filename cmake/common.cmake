# the common configuration for cmake
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

# configurations for cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS true)         # generate compile_commands.json automatically
set(CMAKE_CXX_STANDARD 20)                      # C++20/C17(if needed)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)
set(IPDF_UT_PREFIX ipdf_ut)

# variables
# NOTE: variables with lower-case are private.
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# configurations for compilers(llvm/gnu)
add_library(compiler INTERFACE)

target_compile_options(
    compiler
    INTERFACE
        # BUILD_INTERFACE: options effective for this repo only.
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

target_compile_definitions(
    compiler
    INTERFACE
    "$<${msvc_cxx}:_CRT_SECURE_NO_WARNINGS>"
)

target_include_directories(
    compiler
    INTERFACE
        ${CMAKE_BINARY_DIR}
)

# platform
if (CMAKE_HOST_APPLE)
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
    set(CMAKE_OSX_ARCHITECTURES "arm64")
elseif (CMAKE_HOST_WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows)
    message(STATUS "vcpkg triplet: ${VCPKG_TARGET_TRIPLET}")
endif()

# EOF
