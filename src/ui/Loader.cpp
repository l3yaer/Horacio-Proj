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


void Map::Loader::download_tile_job_entry (void *data)
{
	auto content = (std::pair<Map::Loader *, Map::Tile *> *)data;
	content->first->download_image (content->second);
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
			JobManager::instance ().add_job (Map::Loader::download_tile_job_entry, data);
			return;
		}
	if (Filesystem::file_size (filename) == 0)
		{
			Filesystem::delete_file (filename);
			auto *data = new std::pair<Map::Loader *, Map::Tile *> (this, &tile);
			JobManager::instance ().add_job (Map::Loader::download_tile_job_entry, data);
			return;
		}

	open_image (&tile);
}

void Map::Loader::open_image (Map::Tile *tile)
{
	std::string filename = dir + tile->get_filename (extension);
	Texture *texture = TextureManager::instance ().create (tile->get_filename (), filename);
	texture->load ();
	texture->ready ();
	tile->texture = texture;
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

	std::ofstream *file = Filesystem::create_file (dir + filename);
	int res = Filesystem::download (url, file);
	file->close ();

	if (res == 0)
		open_image (tile);

	delete file;
}