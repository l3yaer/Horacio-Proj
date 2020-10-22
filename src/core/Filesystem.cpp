#include "Filesystem.h"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <limits>
#include <sstream>
#include <sys/stat.h>
#include <curl/curl.h>
#include <iostream>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */

int Filesystem::create_dir(const std::string &path, mode_t mode)
{
	struct stat st;

	if (stat(path.c_str(), &st) != 0) {
		if (mkdir(path.c_str(), mode) != 0 && errno != EEXIST)
			return -1;
	} else if (!S_ISDIR(st.st_mode)) {
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
	while (status == 0 && (sp = strchr(pp, '/')) != 0) {
		if (sp != pp) {
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
	file.clear();
	file.seekg(0, std::ios_base::beg);
	return length;
}

std::string Filesystem::c_path(const std::string &file_path)
{
	std::string file;
	file.reserve(file_path.size());
	for (const char c : file_path)
		if (c == '/')
			file += "//";
		else
			file += c;
	return file;
}

std::string Filesystem::load_file_content(const std::string &file_path)
{
	std::ifstream file;
	std::stringstream string_stream;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	file.open(file_path.c_str());
	string_stream << file.rdbuf();
	file.close();

	return string_stream.str();
}

std::ofstream *Filesystem::create_file(const std::string &file_path)
{
	std::string file = c_path(file_path);
	return new std::ofstream(file, std::ios::binary);
}

void Filesystem::delete_file(const std::string &file_path)
{
	remove(c_path(file_path).c_str());
}

static size_t download_write_callback(char *contents, size_t size, size_t nmemb, void *user_data)
{
	auto *out = static_cast<std::ofstream *>(user_data);
	size_t nbytes = size * nmemb;
	out->write(contents, nbytes);
	return nbytes;
}

int Filesystem::download(const std::string &url, const std::ofstream *out_stream)
{
	CURL *curl = curl_easy_init();
	if (curl == nullptr) {
		std::cerr << "Failed to initialize curl" << std::endl;
		return -1;
	}

	char error_message[CURL_ERROR_SIZE];
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, download_write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, out_stream);
	curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_message);

	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (res != CURLE_OK) {
		std::cerr << "Failed to download: " << url << " " << error_message << std::endl;
	}

	return res;
}

bool Filesystem::rename_file(const std::string &src, const std::string &dst)
{
	return rename(src.c_str(), dst.c_str()) == 0;
}
