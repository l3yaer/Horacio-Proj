#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <Resource.h>

struct SDL_Surface;

class Texture : public Resource {
public:
	unsigned int id;
	int width;
	int height;
	unsigned int format;
	int internal_format;
	std::string file;

	Texture(ResourceCallback *creator, const std::string &name, Handler handler, bool discard_pixels = true);

	virtual ~Texture() = default;

	void use();

protected:
	size_t check_size() override;

	void unready() override;
	void clear_out() override;
	void load_in() override;
	void prepare() override;

	void setTextureFormat(SDL_Surface **);

private:
	void *pixels;
	size_t pixel_size;
	bool discard_pixels;

	void create();

	void set_pixels(void *source, unsigned bytes_per_row);
};

#endif //_TEXTURE_H_
