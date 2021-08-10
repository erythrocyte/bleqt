#include "logger.hpp"

#include <fstream>

#include "boost/log/trivial.hpp"
#include "boost/log/utility/setup.hpp"
#include <boost/core/null_deleter.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

namespace ble_src::logging {

typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;

// Initialize terminal logger
void init_term()
{
    // Initialize sinks
    // create sink to stdout
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
    boost::shared_ptr<std::ostream> stream(&std::clog, boost::null_deleter());
    sink->locked_backend()->add_stream(stream);

    // flush
    sink->locked_backend()->auto_flush(true);

    // format sink
    sink->set_formatter(
        expr::stream
        << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
        << " <" << boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity") << "> "
        << ": "
        << expr::smessage);

    // filter
    // TODO add any filters
    sink->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

    // register sink
    boost::log::core::get()->add_sink(sink);
}

// Initialize logfile
void init_logfile(const std::string logfilename)
{
    // create sink to logfile
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
    sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>(logfilename.c_str()));

    // flush
    sink->locked_backend()->auto_flush(true);

    // format sink

    /* log formatter:
	* [TimeStamp] [ThreadId] [Severity Level] [Scope] Log message
	*/
    auto fmtTimeStamp = boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S");
    auto fmtThreadId = boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID");
    auto fmtSeverity = boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity");
    boost::log::formatter logFmt = boost::log::expressions::format("[%1%] (%2%) [%3%] %4%")
        % fmtTimeStamp % fmtThreadId % fmtSeverity % boost::log::expressions::smessage;

    sink->set_formatter(logFmt);

    // filter
    // TODO add any filters

    // register sink
    boost::log::core::get()->add_sink(sink);
}

void init_log(std::string const logfn)
{
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

    init_term();
    init_logfile(logfn);

    boost::log::add_common_attributes();
}

void write_log(std::string const message, SeverityLevelEnum level)
{
    switch (level) {
    case SeverityLevelEnum::kTrace:
        BOOST_LOG_TRIVIAL(trace) << message;
        break;
    case SeverityLevelEnum::kDebug:
        BOOST_LOG_TRIVIAL(debug) << message;
        break;
    case SeverityLevelEnum::kInfo:
        BOOST_LOG_TRIVIAL(info) << message;
        break;
    case SeverityLevelEnum::kWarning:
        BOOST_LOG_TRIVIAL(warning) << message;
        break;
    case SeverityLevelEnum::kError:
        BOOST_LOG_TRIVIAL(error) << message;
        break;
    case SeverityLevelEnum::kFatal:
        BOOST_LOG_TRIVIAL(fatal) << message;
        break;
    default:
        std::runtime_error("Bad log level to write to the log");
    }
}

void write_log(std::string const message, SeverityLevelEnum level, std::string const methodName, int lineIndex)
{
    std::ostringstream oss;
    if (lineIndex == -1) {
        oss.str("");
        oss.clear();
        oss << methodName << "():: " << message;
    } else {
        oss.str("");
        oss.clear();
        oss << "{ " << methodName << "(" << lineIndex << ") }:: " << message;
    }

    write_log(oss.str(), level);
}

}
