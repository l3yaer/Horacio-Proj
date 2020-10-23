#ifndef _LOG_H_
#define _LOG_H_

#include <sstream>
#include <string>
#include "Singleton.h"

enum LogLevel { ERROR, WARNING, INFO, DEBUG };

class Log {
public:
	Log(const std::string &name);

	std::ostringstream &get(LogLevel level = INFO);
	std::string contents();

	std::string name;

protected:
	std::ostringstream os;

private:
	Log(const Log &);
	Log &operator=(const Log &);

	std::string level_string(LogLevel level);
};

#endif
