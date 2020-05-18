#include <sstream>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <curl/curl.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <JobManager.h>
#include <Filesystem.h>

#include "Loader.h"
#include "Tile.h"
#include "TextureFactory.h"

void Map::Loader::download_tile_job_entry (void *data)
{
  auto content = (std::pair<Map::Loader *, Map::Tile *> *)data;
  content->first->download_image (content->second);
}

Map::Loader::Loader (uint16_t max_zoom, const std::string &prefix, const std::string &extension,
					 const std::string &dir)
	: max_zoom (max_zoom), prefix (prefix), extension (extension), dir (dir)
{
  start ();
}

Map::Loader::~Loader ()
{
  stop ();
}

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

  open_image (tile);
}

void Map::Loader::open_image (Map::Tile &tile)
{
  std::string filename = dir + tile.get_filename (extension);
  Texture *texture = TextureFactory::create (filename);
  tile.texture = texture;
}

void Map::Loader::start ()
{

}

void Map::Loader::stop ()
{
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

  FILE *fp = Filesystem::create_file(dir + filename);

  char errorMessage[CURL_ERROR_SIZE];

  int res = download_file (url, fp, errorMessage);

  if (res != CURLE_OK)
	{
	  std::cerr << "Failed to download: " << url << " " << errorMessage << std::endl;
	}
  else
	{
	  tile->texture = new Texture ();
	  std::cout << "File downloaded: " << url << std::endl;
	}
}

int Map::Loader::download_file (const std::string &url, FILE *out, char *out_msg)
{
  CURL *curl = curl_easy_init ();
  if (curl == nullptr)
	{
	  std::cerr << "Failed to initialize curl" << std::endl;
	  return -1;
	}

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str ());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
  curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, out_msg);

  CURLcode res = curl_easy_perform (curl);
  fclose (out);
  curl_easy_cleanup (curl);

  return res;
}