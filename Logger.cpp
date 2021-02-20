#include "Logger.h"
#include <string>

Logger::Logger(const std::string& logFile, loglevel level)
{
	_logFile = logFile;
	_level = level;
	_log = LoggerImpl::getInstance();
}
