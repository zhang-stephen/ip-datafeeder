// common definitions for ip-datafeeder
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#include <cstdint>
#include <string>

namespace datafeeder
{
// TODO: for unicode support in the future(ASCII only for now)
using string = std::string;

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

// EOF
