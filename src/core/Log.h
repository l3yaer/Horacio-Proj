#ifndef _LOG_H_
#define _LOG_H_

#include <sstream>
#include <string>
#include "Singleton.h"


class Log {
public:
	enum LogLevel { LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG };

	Log(const std::string &name);

	std::ostringstream &get(LogLevel level = LogLevel::LOG_INFO);
	std::string contents();

	std::string name;

protected:
	std::ostringstream os;

private:
	Log(const Log &);

	std::string level_string(LogLevel level);
};

#endif
