// common definitions for ip-datafeeder
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

#include <cstdint>

namespace ipdf
{
// platform definitions
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
}

// EOF
