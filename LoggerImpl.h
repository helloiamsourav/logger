#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "LoggerEnums.h"
#include <iostream>
#include <fstream>
#include <mutex>

class LoggerImpl
{
	static LoggerImpl* _instance;
	static std::mutex _loggerMutex;
	std::mutex _loggingMutex;
	LoggerImpl();

	template<typename T>
	void _logger(loglevel, const T&, const std::string&);

	std::string _getCurrentTimestamp();
	public:
	static LoggerImpl* getInstance();

	template<typename T>
	void trace(const T&  val, const std::string&);

	template<typename T>
	void debug(const T&  val, const std::string&);

	template<typename T>
	void error(const T&  val, const std::string&);
};
template<typename T>
void LoggerImpl::_logger(loglevel level, const T& message, const std::string& logFile)
{
        std::string levelStr;
        if(level == loglevel::trace)
                levelStr = "TRACE";
        if(level == loglevel::debug)
                levelStr = "DEBUG";
        if(level == loglevel::error)
                levelStr = "ERROR";
        {
                std::lock_guard<std::mutex> lock(_loggingMutex);
		std::ofstream outFile;
		outFile.open(logFile, std::ios::out | std::ios::app);
                outFile << "[" <<_getCurrentTimestamp() << ":" << levelStr << "] "<< message << std::endl;
		outFile.close();
        }
}

template<typename T>
void LoggerImpl::trace(const T&  message, const std::string& logFile)
{
        _logger(loglevel::trace, message, logFile);
}

template<typename T>
void LoggerImpl::debug(const T&  message, const std::string& logFile)
{
        _logger(loglevel::debug, message, logFile);
}

template<typename T>
void LoggerImpl::error(const T&  message, const std::string& logFile)
{
        _logger(loglevel::error, message, logFile);
}

#endif
