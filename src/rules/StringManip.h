#ifndef _STRINGMANIP_H_
#define _STRINGMANIP_H_

#include <string>
#include <sstream>
#include <iomanip>

namespace StringManip
{
template <class T> std::string to_string(const T &obj)
{
	std::ostringstream stream;
	stream << std::setprecision(7) << std::fixed << obj;
	return stream.str();
}

inline bool starts_with(const std::string string, const std::string &prefix)
{
	if (string.size() < prefix.size())
		return false;

	for (size_t i = 0; i < prefix.size(); i++)
		if (string.at(i) != prefix.at(i))
			return false;

	return true;
}
}; // namespace StringManip

#endif //_STRINGMANIP_H_
