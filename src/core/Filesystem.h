#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <string>

namespace Filesystem
{
int create_dir(const std::string &path);
int create_path(const std::string &path);
bool file_exists(const std::string &filename);
int file_size(const std::string &filename);
std::string c_path(const std::string &file_path);
std::string load_file_content(const std::string &file_path);
std::ofstream *create_file(const std::string &file_path);
void delete_file(const std::string &file_path);
int download(const std::string &url, const std::ofstream *out_stream);
bool rename_file(const std::string &src, const std::string &dst);
}; // namespace Filesystem

#endif //_FILESYSTEM_H_
