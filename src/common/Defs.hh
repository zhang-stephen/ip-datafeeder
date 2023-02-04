// common definitions for ip-datafeeder
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_COMMON_DEFS_HH
#define __IPDF_COMMON_DEFS_HH

#include <cstdint>
#include <string>

namespace ipdf
{
// TODO: for unicode support in the future(ASCII only for now)
using string = std::string;
using string_view = std::string_view;

// platform definitions
enum class TargetPlatform : uint8_t
{
    WIN32_MSVC,
    WIN32_MSYS,
    LINUX,
    APPLE,
    UNKNOWN,
};

enum class TargetArch : uint8_t
{
    AMD64,
    ARM64,
    UNKNOWN,
};
}

#endif // __IPDF_COMMON_DEFS_HH

// EOF
