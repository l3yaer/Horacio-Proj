#include <memory>
#include <sstream>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <zconf.h>

#include "Loader.h"
#include "Tile.h"
#include "Filesystem.h"
#include "TileFactory.h"
#include "TextureFactory.h"


Map::Loader::Loader(bool tms, bool zxy, uint16_t max_zoom, const std::string &prefix, const std::string &extension,
                    const std::string &dir)
        : tms(tms), zxy(zxy), max_zoom(max_zoom), prefix(prefix), extension(extension), dir(dir)
{
    start();
}

Map::Loader::~Loader()
{
    stop();
}

uint16_t Map::Loader::get_max_zoom() const
{
    return max_zoom;
}

void Map::Loader::load_image(Map::Tile &tile)
{
    std::string filename = dir + tile.get_filename(tms, zxy, extension);

    std::cout << "Tile: " << tile.latitude << " " << tile.longitude << std::endl;
    if (!Filesystem::file_exists(filename))
    {
        download_image(&tile);
        return;
    }
    if (Filesystem::file_size(filename) == 0)
    {
        remove(Filesystem::make_c_path(filename).c_str());
        download_image(&tile);
        return;
    }

    open_image(tile);
}

void Map::Loader::open_image(Map::Tile &tile)
{
    std::string filename = dir + tile.get_filename(tms, zxy, extension);
    Texture* texture = TextureFactory::create(filename);
    tile.texture = texture;
}

void Map::Loader::start()
{

}

void Map::Loader::stop()
{

}

void Map::Loader::download_image(Map::Tile *tile)
{
    std::stringstream dirname;
    dirname << dir << tile->zoom << "/" << tile->latitude;
    std::string path = dirname.str();
    if (Filesystem::create_path(path, 0777) != 0)
        std::cerr << getpid() << ": failed to create " << errno << " - " << path << std::endl;
    std::string filename = tile->get_filename(tms, zxy, extension);
    std::string url = prefix + filename;

    FILE *fp = get_file(filename);

    char errorMessage[CURL_ERROR_SIZE];

    int res = download_file(url, fp, errorMessage);

    if (res != CURLE_OK)
    {
        std::cerr << "Failed to download: " << url << " " << errorMessage << std::endl;
    } else
    {
        tile->texture = new Texture();
        std::cout << "File downloaded: " << url << std::endl;
    }
}

FILE *Map::Loader::get_file(const std::string &filename) const
{
    const std::string file_path = this->dir + filename;
    std::string file = Filesystem::make_c_path(file_path);

    return fopen(file.c_str(), "wb");
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int Map::Loader::download_file(const std::string &url, FILE *out, char *out_msg)
{
    CURL *curl = curl_easy_init();
    if (curl == nullptr)
    {
        std::cerr << "Failed to initialize curl" << std::endl;
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);

    curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);

    // Disable certificate verification in order to support CURL/OpenSSL
    // without system-specific capath configuration via Conan
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

    // Buffer for error message
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, out_msg);

    CURLcode res = curl_easy_perform(curl);
    fclose(out);
    curl_easy_cleanup(curl);

    return res;
}