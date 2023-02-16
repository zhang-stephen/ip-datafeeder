// the base class of ipdf exception
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

#include <exception>

namespace ipdf::utility
{
class IpdfException : public std::exception
{
};
} // namespace ipdf::utility

// EOF
