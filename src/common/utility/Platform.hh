// Platform-dependent utilities
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

#include <cstdint>

namespace ipdf::utility
{
enum class TargetPlatform : uint8_t
{
    Win32VisualCpp,
    Win32Mingw,
    Linux,
    Apple,
    UNKNOWN,
};

enum class TargetArch : uint8_t
{
    AMD64,
    ARM64,
    UNKNOWN,
};

inline constexpr TargetPlatform platform()
{
#ifdef __APPLE__
    return TargetPlatform::Apple;
#elif defined(__LINUX__)
    return TargetPlatform::Linux;
#elif defined(_WIN32) || defined(_WIN64)
#ifdef _MSC_VER
    return TargetPlatform::Win32VisualCpp;
#else // FIXME: To be confirmed the name of the macro of MSYS2.
    return TargetPlatform::Win32Mingw;
#endif // _MSC_VER
#else
#error "Unknown Platform to Build!"
#endif // __APPLE__, __LINUX__, __WIN32__
}

inline constexpr TargetArch architecture()
{
#ifdef __aarch64__
    return TargetArch::ARM64;
#elif defined(__amd64) || defined(_M_AMD64)
    return TargetArch::AMD64;
#else
#error "Unknown Architecture to Build"
#endif // __aarch64__
}

// clang-format off
inline constexpr bool isWin32Msvc() { return platform() == TargetPlatform::Win32VisualCpp; }
inline constexpr bool isWin32Msys() { return platform() == TargetPlatform::Win32Mingw; }
inline constexpr bool isMacOs() { return platform() == TargetPlatform::Apple; }
inline constexpr bool isLinux() { return platform() == TargetPlatform::Linux; }
inline constexpr bool isWin32() { return isWin32Msvc() || isWin32Msys(); }
inline constexpr bool isArm64() { return architecture() == TargetArch::ARM64; }
inline constexpr bool isAmd64() { return architecture() == TargetArch::AMD64; }
// clang-format on
} // namespace ipdf::utility

// EOF
