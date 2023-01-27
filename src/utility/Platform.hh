// Platform-dependent utilities
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IP_DATAFEEDER_UTILITY_PLATFORM_HH
#define __IP_DATAFEEDER_UTILITY_PLATFORM_HH

#include "Defs.hh"

namespace datafeeder::utility
{
inline constexpr TargetPlatform platform()
{
#ifdef __APPLE__
    return TargetPlatform::APPLE;
#elif defined(__LINUX__)
    return TargetPlatform::LINUX;
#elif defined(__WIN32__)
#ifdef __MSVC__
    return TargetPlatform::WIN32_MSVC;
#else // FIXME: To be confirmed the name of the macro of MSYS2.
    return TargetPlatform::WIN32_MSYS;
#endif // __MSVC__
#else
#error "Unknown Platform to Build!"
#endif // __APPLE__, __LINUX__, __WIN32__
}

inline constexpr TargetArch architecture()
{
#ifdef __aarch64__
    return TargetArch::ARM64;
#else
#error "Unknown Architecture to Build"
#endif // __aarch64__
}

inline constexpr bool isWin32Msvc() { return platform() == TargetPlatform::WIN32_MSVC; }
inline constexpr bool isWin32Msys() { return platform() == TargetPlatform::WIN32_MSYS; }
inline constexpr bool isMacOs() { return platform() == TargetPlatform::APPLE; }
inline constexpr bool isLinux() { return platform() == TargetPlatform::LINUX; }
inline constexpr bool isWin32() { return isWin32Msvc() || isWin32Msys(); }
inline constexpr bool isArm64() { return architecture() == TargetArch::ARM64; }
inline constexpr bool isAmd64() { return architecture() == TargetArch::AMD64; }
} // namespace datafeeder::utility

#endif // __IP_DATAFEEDER_UTILITY_PLATFORM_HH

// EOF
