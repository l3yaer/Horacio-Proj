#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <Resource.h>

struct SDL_Surface;

class Texture : public Resource
{
 public:
  unsigned int id;
  int width;
  int height;
  unsigned int format;
  int internal_format;
	std::string file;

  Texture (ResourceManager *creator, const std::string &name, Handler handler);

  virtual ~Texture () = default;

  void create (bool discard_pixels = true);

  void set_pixels (void *source, unsigned bytes_per_row);

  void use ();

 protected:
	size_t check_size () override;

	void unready () override;
	void clear_out () override;
	void load_in () override;
	void prepare () override;

	void setTextureFormat (SDL_Surface **);
 private:
  void *pixels;
	size_t pixel_size;
};

#endif //_TEXTURE_H_
