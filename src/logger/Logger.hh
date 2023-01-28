// ** IMPORTANT **
// A wrapper of https://github.com/gabime/spdlog, branch v1.x
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IP_DATAFEEDER_LOGGER_HH
#define __IP_DATAFEEDER_LOGGER_HH

#include "Defs.hh"

#include <memory>
#include <spdlog/spdlog.h>

namespace datafeeder::logger
{
extern std::shared_ptr<spdlog::logger> g_ipdfLogger;

void setupSpdLog();
} // namespace datafeeder::logger

// log interfaces wrapper
#define IPDF_LOG_TRC(...) SPDLOG_LOGGER_TRACE(datafeeder::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_DBG(...) SPDLOG_LOGGER_DEBUG(datafeeder::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_INF(...) SPDLOG_LOGGER_INFO(datafeeder::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_WRN(...) SPDLOG_LOGGER_WARN(datafeeder::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_ERR(...) SPDLOG_LOGGER_ERROR(datafeeder::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_CRI(...) SPDLOG_LOGGER_CRITICAL(datafeeder::logger::g_ipdfLogger, __VA_ARGS__)

#endif // __IP_DATAFEEDER_LOGGER_HH

// EOF
