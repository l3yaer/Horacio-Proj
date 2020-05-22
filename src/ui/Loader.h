#ifndef _LOADER_H_
#define _LOADER_H_

#include <cstdint>
#include <string>

namespace Map
{
class Tile;

class Loader
{
 private:
  Loader (const Loader &) = delete;

  static void start ();

  static void stop ();

  uint16_t max_zoom;

  const std::string prefix;
  const std::string extension;
  const std::string dir;

  static void download_tile_job_entry (void *data);

  void download_image (Tile *tile);

 public:
  Loader (uint16_t max_zoom, const std::string &prefix, const std::string &extension,
		  const std::string &dir);

  ~Loader ();

  void load_image (Tile &tile);

  void open_image (Tile &tile);

  uint16_t get_max_zoom () const;
};
}

#endif //_LOADER_H_
