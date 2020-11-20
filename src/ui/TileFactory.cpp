#include "TileFactory.h"
#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <JobManager.h>
#include <Filesystem.h>
#include "Tile.h"
#include "Square.h"
#include "TextureManager.h"
#include "MeshManager.h"

void texture_factory_download_tile(void *data)
{
	auto content = (std::pair<TileFactory *, Tile *> *)(data);
	if (content == nullptr || content->first == nullptr || content->second == nullptr)
		return;
	content->first->download_image(content->second);
}

TileFactory::TileFactory(const std::string &prefix, const std::string &extension, const std::string &dir) :
	 prefix(prefix), extension(extension), dir(dir)
{
}

TileFactory::~TileFactory()
{
	tiles.clear();
}

std::string TileFactory::tile_id(uint16_t zoom, uint64_t x, uint64_t y)
{
	std::stringstream ss;
	ss << zoom << "/" << x << "/" << y;
	return ss.str();
}

Tile *TileFactory::get_tile(uint16_t zoom, int x, int y)
{
	auto key = tile_id(zoom, x, y);
	auto i = tiles.find(key);

	if (i != tiles.end())
		return i->second;

	Tile *tile = new Tile(zoom, x, y, nullptr);
	load_image(*tile);
	tile->mesh = MeshManager::instance().create_shape<float>("square", 1.0f);
	tiles[key] = tile;
	return tile;
}

void TileFactory::load_image(Tile &tile)
{
	std::string filename = dir + tile.get_filename(extension);

	if (!Filesystem::file_exists(filename)) {
		auto *data = new std::pair<TileFactory *, Tile *>(this, &tile);
		JobManager::instance().add_job(texture_factory_download_tile, data,  JobManager::Queue::LOW);
		return;
	}
	if (Filesystem::file_size(filename) == 0) {
		Filesystem::delete_file(filename);
		auto *data = new std::pair<TileFactory *, Tile *>(this, &tile);
		JobManager::instance().add_job(texture_factory_download_tile, data,  JobManager::Queue::LOW);
		return;
	}

	open_image(&tile);
}

void TileFactory::open_image(Tile *tile)
{
	std::string filename = dir + tile->get_filename(extension);
	if (!Filesystem::file_exists(filename) || Filesystem::file_size(filename) == 0)
		return;
	tile->texture = TextureManager::instance().create(tile->get_filename(), filename);
}

void TileFactory::download_image(Tile *tile)
{
	std::stringstream dirname;
	dirname << dir << tile->zoom << "/" << tile->x;
	std::string path = dirname.str();
	if (Filesystem::create_path(path, 0777) != 0)
		std::cerr << "failed to create " << errno << " - " << path << std::endl;
	std::string filename = tile->get_filename(extension);
	std::string url = prefix + filename;
	std::string temp_file = dir + filename + ".temp";

	std::ofstream *file = Filesystem::create_file(temp_file);
	int res = Filesystem::download(url, file);
	file->close();

	if (res == 0)
		Filesystem::rename_file(temp_file, dir + filename);

	delete file;
}
