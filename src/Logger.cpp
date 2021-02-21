#include "Logger.h"
#include <string>

Logger::Logger(const std::string& logFile, loglevel level)
{
	_logFile = logFile;
	_level = level;
	_log = LoggerImpl::getInstance();
}

Logger& Logger::operator<<(std::ostream& (*var)(std::ostream&))
{
	_flushBuffer();
	return *this;
}
void Logger::_writeToBuffer(const std::stringstream& ss)
{
	std::lock_guard<std::mutex> lock(_bufferMtx);
	_buffer << ss.str();
}
void Logger::_flushBuffer()
{
	std::lock_guard<std::mutex> lock(_bufferMtx);
	if(_level == loglevel::trace)
		_log->trace(_buffer.str(), _logFile);
	if(_level == loglevel::debug)
		_log->debug(_buffer.str(), _logFile);
	if(_level== loglevel::error)
		_log->error(_buffer.str(), _logFile);
	_buffer.str("");
}
