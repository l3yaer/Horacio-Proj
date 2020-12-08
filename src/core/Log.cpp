#include "Log.h"

const std::string current_date_time()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%X", &tstruct);

	return buf;
}

Log::Log(const std::string &name) : name(name)
{
}

std::ostringstream &Log::get(LogLevel level)
{
	os << std::endl;
	os << current_date_time();
	os << " - " << level_string(level);
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
