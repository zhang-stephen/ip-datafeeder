// ** IMPORTANT **
// A wrapper of https://github.com/gabime/spdlog, branch v1.x
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace ipdf::logger
{
extern std::shared_ptr<spdlog::logger> g_ipdfLogger;

void setupSpdLog();
} // namespace ipdf::logger

// log interfaces wrapper
#define IPDF_LOG_TRC(...) SPDLOG_LOGGER_TRACE(ipdf::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_DBG(...) SPDLOG_LOGGER_DEBUG(ipdf::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_INF(...) SPDLOG_LOGGER_INFO(ipdf::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_WRN(...) SPDLOG_LOGGER_WARN(ipdf::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_ERR(...) SPDLOG_LOGGER_ERROR(ipdf::logger::g_ipdfLogger, __VA_ARGS__)
#define IPDF_LOG_CRI(...) SPDLOG_LOGGER_CRITICAL(ipdf::logger::g_ipdfLogger, __VA_ARGS__)

// EOF
