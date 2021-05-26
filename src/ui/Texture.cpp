#include <glad/glad.h>
#include <algorithm>
#include <cstring>
#include "graphics.h"
#include <LogManager.h>
#include "Texture.h"

unsigned int dummy = -1;

Texture::Texture(ResourceCallback *creator, const std::string &name, Handler handler, bool discard_pixels)
		: Resource(creator, name, handler), pixels(nullptr), width(0), height(0), format(0), internal_format(0),
		  discard_pixels(discard_pixels)
{
	if (dummy == -1) {
		glGenTextures(1, &dummy);
		glBindTexture(GL_TEXTURE_2D, dummy);

		unsigned char empty[3] = { 0, 0, 0 };
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, empty);
	}

	this->id = dummy;
}

void Texture::use()
{
	if (is_ready())
		glBindTexture(GL_TEXTURE_2D, id);
}

size_t Texture::check_size()
{
	return Resource::check_size() + (discard_pixels ? 0 : pixel_size);
}

void Texture::unready()
{
	glDeleteTextures(1, &id);
}

void Texture::clear()
{
	if (pixels)
		free(pixels);
}

void Texture::load_in()
{
	SDL_Surface *surface = IMG_Load(file.c_str());

	if (surface == NULL)
		return;

	if (SDL_MUSTLOCK(surface)) {
		SDL_LockSurface(surface);
	}

	setTextureFormat(&surface);

	height = surface->h;
	width = surface->w;
	set_pixels(surface->pixels, surface->pitch);

	if (SDL_MUSTLOCK(surface)) {
		SDL_UnlockSurface(surface);
	}

	SDL_FreeSurface(surface);
}

void Texture::prepare()
{
	create();
}

void Texture::create()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (discard_pixels) {
		free(pixels);
		pixels = nullptr;
		pixel_size = 0;
	}
}

void Texture::set_pixels(void *source, unsigned int bytes_per_row)
{
	typedef uint8_t byte_type;

	const byte_type *originalRaw = static_cast<byte_type *>(source);
	byte_type *flippedRaw = new byte_type[bytes_per_row * height];

	for (unsigned i = 0; i < height; ++i) {
		const byte_type *srcBeg = originalRaw + (bytes_per_row * (height - i - 1));
		const byte_type *srcEnd = srcBeg + bytes_per_row;

		std::copy(srcBeg, srcEnd, flippedRaw + bytes_per_row * i);
	}

	pixel_size = sizeof(byte_type) * bytes_per_row * height;
	pixels = malloc(pixel_size);
	memcpy(pixels, flippedRaw, pixel_size);
	delete[] flippedRaw;
}

void Texture::setTextureFormat(SDL_Surface **surface)
{
	if ((*surface)->format->BytesPerPixel == 4) {
		if ((*surface)->format->Rmask == 0x000000ff) {
			format = GL_RGBA;
			internal_format = GL_RGBA8;
		} else {
			format = GL_BGRA;
			internal_format = GL_RGBA8;
		}
	} else if ((*surface)->format->BytesPerPixel == 3) {
		if ((*surface)->format->Rmask == 0x000000ff) {
			format = GL_RGB;
			internal_format = GL_RGB8;
		} else {
			format = GL_BGR;
			internal_format = GL_RGB8;
		}
	} else {
		SDL_PixelFormat *pformat = SDL_AllocFormat(SDL_PIXELFORMAT_BGR24);
		SDL_Surface *tmp = SDL_ConvertSurface((*surface), pformat, 0);
		format = GL_BGR;
		internal_format = GL_RGB8;
		if (SDL_MUSTLOCK((*surface))) {
			SDL_UnlockSurface((*surface));
		}
		SDL_FreeSurface((*surface));
		(*surface) = tmp;
		if (SDL_MUSTLOCK((*surface))) {
			SDL_LockSurface((*surface));
		}
	}
}
