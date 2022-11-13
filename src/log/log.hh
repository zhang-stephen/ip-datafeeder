#ifndef __IP_DATAFEEDER_LOG_HH
#define __IP_DATAFEEDER_LOG_HH

#include <boost/log/sinks.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/shared_ptr.hpp>

#define LOG_DEBUG BOOST_LOG_SEV(datafeeder::logger::get(), datafeeder::Severity::DBG)
#define LOG_INFO BOOST_LOG_SEV(datafeeder::logger::get(), datafeeder::Severity::INF)
#define LOG_WARNING BOOST_LOG_SEV(datafeeder::logger::get(), datafeeder::Severity::WRN)
#define LOG_ERROR BOOST_LOG_SEV(datafeeder::logger::get(), datafeeder::Severity::ERR)
#define LOG_CRITICAL BOOST_LOG_SEV(datafeeder::logger::get(), datafeeder::Severity::CRI)
#define LOG_EXCEPTION BOOST_LOG_SEV(datafeeder::logger::get(), datafeeder::Severity::EXP)
#define LOG_FLUSH()                                                                                                    \
    do {                                                                                                               \
        datafeeder::logger::flush();                                                                                   \
    } while (false)

namespace datafeeder
{
enum Severity : uint8_t
{
    DBG, // debug
    INF, // info
    WRN, // warning
    ERR, // error
    CRI, // critical
    EXP, // exception
};

namespace
{
namespace logging = boost::log;
namespace src     = logging::sources;
namespace sinks   = logging::sinks;
} // namespace

class logger
{
public:
    logger()              = default;
    logger(const logger&) = delete;
    logger(logger&&)      = delete;

    using _text_sink_t = typename sinks::asynchronous_sink<sinks::text_ostream_backend>;
    using _logger_t    = src::severity_logger_mt<Severity>;

    inline static void       flush() { _sink->flush(); }
    inline static _logger_t& get() { return _lg; }
    static void              init();

private:
    inline static boost::shared_ptr<_text_sink_t> _sink { boost::make_shared<_text_sink_t>() };
    inline static _logger_t                       _lg {};
};
} // namespace datafeeder

#endif // __IP_DATAFEEDER_LOG_HH

// EOF