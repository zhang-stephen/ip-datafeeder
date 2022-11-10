/**
 * All declarations, definitions, implementatons and others related with platform, should be defined src/platform/xx.h
 */

#ifndef __IP_DATAFEEDER_PLATFORM_HH
#define __IP_DATAFEEDER_PLATFORM_HH

#include "config.hh"

#ifdef PLATFORM_WINDOWS
#include "platform/windows.hh"
#else
#include "platform/unix.hh"
#endif // PLATFORM_xx

#endif // __IP_DATAFEEDER_PLATFORM_HH

// EOF