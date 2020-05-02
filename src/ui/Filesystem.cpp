#include "Filesystem.h"
#include <cerrno>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */

#include <cstring>
#include <fstream>
#include <limits>


int Filesystem::create_dir(const std::string &path, mode_t mode)
{
    struct stat st;

    if (stat(path.c_str(), &st) != 0)
    {
        /* Directory does not exist. EEXIST for race condition */
        if (mkdir(path.c_str(), mode) != 0 && errno != EEXIST)
            return -1;
    } else if (!S_ISDIR(st.st_mode))
    {
        errno = ENOTDIR;
        return -1;
    }

    return 0;
}

int Filesystem::create_path(const std::string &path, mode_t mode)
{
    char *pp;
    char *sp;
    int status;
    char *copy_path = strdup(path.c_str());

    status = 0;
    pp = copy_path;
    while (status == 0 && (sp = strchr(pp, '/')) != 0)
    {
        if (sp != pp)
        {
            *sp = '\0';
            status = create_dir(copy_path, mode);
            *sp = '/';
        }
        pp = sp + 1;
    }
    if (status == 0)
        status = create_dir(path, mode);
    free(copy_path);
    return (status);
}

bool Filesystem::file_exists(const std::string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

int Filesystem::file_size(const std::string &filename)
{
    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary);
    file.ignore(std::numeric_limits<std::streamsize>::max());
    std::streamsize length = file.gcount();
    file.clear();   //  Since ignore will have set eof.
    file.seekg(0, std::ios_base::beg);
    return length;
}

std::string Filesystem::make_c_path(const std::string &file_path)
{
    std::string file;
    file.reserve(file_path.size());
    for (const char c : file_path)
        if (c == '/') file += "//";
        else file += c;
    return file;
}
