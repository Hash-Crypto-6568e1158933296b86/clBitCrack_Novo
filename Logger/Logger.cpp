#include <stdio.h>
#include <time.h>

#include "Logger.h"
#include "util.h"

bool LogLevel::isValid(int level)
{
	switch(level) {
		case Info:
		case Error:
		case Debug:
			return true;
		default:
			return false;
	}
}

std::string LogLevel::toString(int level)
{
	switch(level) {
		case Info:
			return "Info";
		case Error:
			return "Error";
		case Debug:
			return "Debug";
        case Warning:
            return "Warning";
	}

	return "";
}

std::string Logger::getDateTimeString()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return std::string(buf);
}

std::string Logger::formatLog(int logLevel, std::string msg)
{
	std::string dateTime = getDateTimeString();

	std::string prefix = "[" + dateTime + "] [" + LogLevel::toString(logLevel) + "] ";

	prefix += msg;

	return prefix;
}


void Logger::log(int logLevel, std::string msg)
{
	std::string str = formatLog(logLevel, msg);

	fprintf(stderr, "%s\n", str.c_str());
}

void Logger::setLogFile(std::string path)
{

}
