#include "Log.h"

Log::Log(const std::string &name) : name(name)
{
}

std::ostringstream &Log::get(LogLevel level)
{
	os << std::endl;
	os << "- " << level_string(level);
	os << " :\t";
	return os;
}

std::string Log::contents()
{
	return os.str();
}

std::string Log::level_string(LogLevel level)
{
	static const char *const levels[] = { "ERROR", "WARNING", "INFO", "DEBUG" };
	return levels[level];
}
