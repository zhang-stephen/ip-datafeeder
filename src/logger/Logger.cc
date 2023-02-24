#include "Logger.hh"

#include <memory>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

namespace ipdf::logger
{
std::shared_ptr<spdlog::logger> g_ipdfLogger;

void setupSpdLog()
{
    // TODO: async console output if needed
    g_ipdfLogger = spdlog::stdout_logger_mt("console");
    spdlog::set_pattern("%L[%Y-%m-%d %H:%M:%S.%e] [%s:%#]: %v", spdlog::pattern_time_type::local);
}
} // namespace ipdf::logger

// EOF
