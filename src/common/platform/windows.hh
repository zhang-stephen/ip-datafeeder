#ifndef __IP_DATAFEEDER_PLATFORM_WINDOWS_HH
#define __IP_DATAFEEDER_PLATFORM_WINDOWS_HH

#include <ws2tcpip.h>

namespace datafeeder
{
using socket_t = ::SOCKET;
}

#endif // __IP_DATAFEEDER_PLATFORM_WINDOWS_HH

// EOF