#include "Logger.hh"

#include <memory>
#include <spdlog/sinks/stdout_sinks.h>

namespace ipdf::logger
{
std::shared_ptr<spdlog::logger> g_ipdfLogger;

void setupSpdLog()
{
    // TODO: async console output if needed
    g_ipdfLogger = spdlog::stdout_logger_mt("console");

    // new patterns...
}
} // namespace ipdf::logger

// EOF
