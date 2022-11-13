#include "log.hh"

#include "utility.hh"

#include <boost/core/null_deleter.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/manipulators/to_log.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/move/core.hpp>
#include <thread>

namespace datafeeder
{
namespace
{
namespace logging = boost::log;
namespace attrs   = logging::attributes;
namespace expr    = logging::expressions;
struct severity_tag;

// Interface class for std::thread::id
class std_current_thread_id : public logging::attribute
{
protected:
    class impl : public logging::attribute::impl
    {
    public:
        logging::attribute_value get_value() { return attrs::make_attribute_value(std::this_thread::get_id()); }
    };

public:
    std_current_thread_id()
        : logging::attribute(new impl())
    {
    }

    explicit std_current_thread_id(attrs::cast_source const& source)
        : logging::attribute(source.as<impl>())
    {
    }
};

inline logging::formatting_ostream& operator<<(logging::formatting_ostream&                         strm,
                                               logging::to_log_manip<Severity, severity_tag> const& manip)
{
    const char* severities[] = {
        "DBG", "INF", "WRN", "ERR", "CRI", "EXP",
    };

    Severity level = manip.get();
    strm << severities[static_cast<size_t>(level)];

    return strm;
}

} // namespace

void logger::init()
{
    constexpr char _log_field_seperator = ' ';

    boost::shared_ptr<std::ostream> _stream { &std::clog, boost::null_deleter() };
    _sink->locked_backend()->add_stream(_stream);
    _sink->locked_backend()->auto_flush(); // FIXME: seems not work

    auto _formatter
        = expr::stream << '[' << expr::format_date_time<boost::posix_time::ptime>("Timestamp", "%H:%M:%S.%f") << ']'
                       << _log_field_seperator << "[Thread: " << expr::attr<std::thread::id>("ThreadId") << ']'
                       << _log_field_seperator << '<' << expr::attr<Severity, severity_tag>("Severity") << '>';

    auto _core = logging::core::get();
    _core->add_sink(_sink);
    _core->add_global_attribute("Timestamp", attrs::local_clock());
    _core->add_global_attribute("ThreadId", std_current_thread_id());

    // TODO: add more attributes and formatters for debugging
    if constexpr (is_build_for_debug()) {}

    _sink->set_formatter(_formatter << ':' << _log_field_seperator << expr::smessage);


}
} // namespace datafeeder

// EOF