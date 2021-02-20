#include "LoggerImpl.h"
#include <string>
#include <sstream>
#include <type_traits>
#include <typeinfo>
class Logger
{
	std::string _logFile;
	LoggerImpl* _log;
	loglevel _level;
	std::string _buffer;
	std::mutex _bufferMtx;

	public:
	Logger(const std::string& logFile, loglevel level);

	template<typename T>
	void operator()(const T& message)
	{
		std::stringstream ss;
                ss << message;
		if(_level == loglevel::trace)
			_log->trace(ss.str(), _logFile);
		if(_level == loglevel::debug)
			_log->debug(ss.str(), _logFile);
		if(_level == loglevel::error)
			_log->error(ss.str(), _logFile);
	}

	template<typename T>
	Logger& operator<<(const T& message)
	{
		if(message == std::endl)
		{
			flushBuffer();
			return *this;
		}
		std::stringstream ss;
		ss << message;
		writeToBuffer(ss.str());
		return *this;
	}
	void writeToBuffer(const std::string& string)
	{
		std::lock_guard<std::mutex> lock(_bufferMtx);
		_buffer = _buffer + string;
	}
	void flushBuffer()
	{
		std::lock_guard<std::mutex> lock(_bufferMtx);
                if(_level == loglevel::trace)
                        _log->trace(_buffer, _logFile);
                if(_level == loglevel::debug)
                        _log->debug(_buffer, _logFile);
                if(_level== loglevel::error)
                        _log->error(_buffer, _logFile);
		_buffer.clear();
	}
};
