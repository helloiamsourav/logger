#include "LoggerImpl.h"
#include <string>

LoggerImpl::LoggerImpl()
{
}
LoggerImpl* LoggerImpl::getInstance()
{
	std::lock_guard<std::mutex> lock(_loggerMutex);
	if(_instance == nullptr)
	{
		_instance = new LoggerImpl();
	}
	return _instance;
}

std::string LoggerImpl::_getCurrentTimestamp()
{
	using std::chrono::system_clock;
	auto currentTime = std::chrono::system_clock::now();
	char buffer[80];
	auto transformed = currentTime.time_since_epoch().count() / 1000000;
	auto millis = transformed % 1000;
	std::time_t tt;
	tt = system_clock::to_time_t ( currentTime );
	auto timeinfo = localtime (&tt);
	strftime (buffer,80,"%F %H:%M:%S",timeinfo);
	sprintf(buffer, "%s:%03d",buffer,(int)millis);

	return std::string(buffer);
}
LoggerImpl* LoggerImpl::_instance{nullptr};
std::mutex LoggerImpl::_loggerMutex;
