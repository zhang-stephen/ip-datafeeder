#ifndef __IP_DATAFEEDER_UTILITY_HH
#define __IP_DATAFEEDER_UTILITY_HH

#include "config.hh"

namespace datafeeder
{
inline constexpr bool is_build_for_release()
{
#ifdef NDEBUG
    return true;
#else
    return false;
#endif
}

inline constexpr bool is_build_for_debug() { return not is_build_for_release(); }

} // namespace datafeeder

#endif // __IP_DATAFEEDER_UTILITY_HH

// EOF