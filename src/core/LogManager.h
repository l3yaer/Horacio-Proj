#ifndef _LOGMANAGER_H_
#define _LOGMANAGER_H_

#include <map>
#include <sstream>
#include "Singleton.h"
#include "Log.h"

class LogManager : public Singleton<LogManager> {
public:
	LogManager();
	~LogManager();

	Log *create_log(const std::string &name, bool default_log = true);

	Log *get_log(const std::string &name);
	Log *get_default_log();

	void destroy_log(const std::string &name);
	void destroy_log(Log *log);

	Log *set_default(Log *log);

	std::ostringstream &log();

private:
	std::map<std::string, Log *> logs;
	Log *default_log;
};

#define LOG() LogManager::instance().log()

#endif
