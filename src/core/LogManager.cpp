#include "LogManager.h"

IMPLEMENT_SINGLETON(LogManager)

LogManager::LogManager() : Singleton<LogManager>()
{
}

LogManager::~LogManager()
{
}

Log *LogManager::create_log(const std::string &name, bool default_log)
{
	Log *log = new Log(name);
	if (default_log)
		this->default_log = log;

	logs[name] = log;

	return log;
}

Log *LogManager::get_log(const std::string &name)
{
	return logs[name];
}

Log *LogManager::get_default_log()
{
	return default_log;
}

void LogManager::destroy_log(const std::string &name)
{
	Log *log = get_log(name);
	logs.erase(name);
	delete log;
}

void LogManager::destroy_log(Log *log)
{
	destroy_log(log->name);
}

Log *LogManager::set_default(Log *log)
{
	return default_log;
}

std::ostringstream &LogManager::log()
{
	return default_log->get();
}
