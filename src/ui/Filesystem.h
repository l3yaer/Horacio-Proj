#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_


#include <sys/stat.h>
#include <string>

class Filesystem
{
public:
    static int create_dir(const std::string& path, mode_t mode);
    static int create_path(const std::string& path, mode_t mode);
    static bool file_exists(const std::string& filename);
    static int file_size(const std::string& filename);
    static std::string make_c_path(const std::string &file_path);
};


#endif //FILESYSTEM_H_
