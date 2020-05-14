#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <string>

class Filesystem
{
 public:
  static int create_dir (const std::string &path, mode_t mode);
  static int create_path (const std::string &path, mode_t mode);
  static bool file_exists (const std::string &filename);
  static int file_size (const std::string &filename);
  static std::string make_c_path (const std::string &file_path);
  static std::string load_file_content (const std::string &file_path);
};

#endif //_FILESYSTEM_H_
