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

typedef std::pair<TileFactory *, Tile *> FactoryTilePair;

void texture_factory_download_tile(void *data)
{
	FactoryTilePair *content = reinterpret_cast<FactoryTilePair *>(data);
	if (content == nullptr || content->first == nullptr || content->second == nullptr)
		return;
	content->first->download_image(content->second);
	delete content;
}

TileFactory::TileFactory(const std::string &prefix, const std::string &extension, const std::string &dir)
		: prefix(prefix), extension(extension), dir(dir)
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
	std::string key = tile_id(zoom, x, y);
	std::map<std::string, Tile *>::iterator i = tiles.find(key);

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
		FactoryTilePair *data = new FactoryTilePair(this, &tile);
		JobManager::instance().add_job(texture_factory_download_tile, data, JobManager::Queue::DEFAULT);
		return;
	}
	if (Filesystem::file_size(filename) == 0) {
		Filesystem::delete_file(filename);
		FactoryTilePair *data = new FactoryTilePair(this, &tile);
		JobManager::instance().add_job(texture_factory_download_tile, data, JobManager::Queue::DEFAULT);
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
