#ifndef BLESRC_LOGGING_LOGGER_H_
#define BLESRC_LOGGING_LOGGER_H_

#include <string>

namespace ble_src::logging {

enum SeverityLevelEnum {
    kTrace,
    kDebug,
    kInfo,
    kWarning,
    kError,
    kFatal,
};

void init_log(const std::string logfn);
void write_log(const std::string message, SeverityLevelEnum level);
void write_log(const std::string message, SeverityLevelEnum level,
    const std::string methodName, int lineIndex = -1);

}

#endif
