// the base class of ipdf exception
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_UTILITY_EXCEPTIONS_HH
#define __IPDF_UTILITY_EXCEPTIONS_HH

#include <exception>

namespace ipdf::utility
{
class IpdfException : public std::exception
{
};
} // namespace ipdf::utility

#endif // __IPDF_UTILITY_EXCEPTIONS_HH

// EOF
