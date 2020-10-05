#include <sstream>
#include <fstream>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <algorithm>
#include <string>
#include <JobManager.h>
#include <Filesystem.h>

#include "Loader.h"
#include "Tile.h"
#include "TextureManager.h"

namespace Map
{

void loader_download_tile (void *data)
{
	auto content = (std::pair<Map::Loader *, Map::Tile *> *)data;
    if(content->first == nullptr || content->second == nullptr) return;
	content->first->download_image (content->second);
}

}

Map::Loader::Loader (uint16_t max_zoom, const std::string &prefix, const std::string &extension,
										 const std::string &dir)
		: max_zoom (max_zoom), prefix (prefix), extension (extension), dir (dir)
{}

uint16_t Map::Loader::get_max_zoom () const
{
	return max_zoom;
}

void Map::Loader::load_image (Map::Tile &tile)
{
	std::string filename = dir + tile.get_filename (extension);

	if (!Filesystem::file_exists (filename))
		{
			auto *data = new std::pair<Map::Loader *, Map::Tile *> (this, &tile);
			JobManager::instance ().add_job (loader_download_tile, data);
			return;
		}
	if (Filesystem::file_size (filename) == 0)
		{
			Filesystem::delete_file (filename);
			auto *data = new std::pair<Map::Loader *, Map::Tile *> (this, &tile);
			JobManager::instance ().add_job (loader_download_tile, data);
			return;
		}

	open_image (&tile);
}

void Map::Loader::open_image (Map::Tile *tile)
{
	std::string filename = dir + tile->get_filename (extension);
	if (!Filesystem::file_exists (filename) || Filesystem::file_size (filename) == 0) return;
	tile->texture = TextureManager::instance ().create (tile->get_filename (), filename);
}

void Map::Loader::download_image (Map::Tile *tile)
{
	std::stringstream dirname;
	dirname << dir << tile->zoom << "/" << tile->x;
	std::string path = dirname.str ();
	if (Filesystem::create_path (path, 0777) != 0)
		std::cerr << "failed to create " << errno << " - " << path << std::endl;
	std::string filename = tile->get_filename (extension);
	std::string url = prefix + filename;
	std::string temp_file = dir + filename + ".temp";

	std::ofstream *file = Filesystem::create_file (temp_file);
	int res = Filesystem::download (url, file);
	file->close ();

	if (res == 0)
		Filesystem::rename_file(temp_file, dir + filename);

	delete file;
}
