#include <glad/glad.h>
#include <algorithm>
#include <cstring>
#include "Texture.h"

unsigned int dummy = 0;

void Texture::create (bool discard_pixels)
{
  glGenTextures (1, &id);
  glBindTexture (GL_TEXTURE_2D, id);

  glTexImage2D (GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
  glGenerateMipmap (GL_TEXTURE_2D);

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  if (discard_pixels)
	{
	  free (pixels);
	  pixels = nullptr;
	}
}

Texture::Texture () : pixels (nullptr), width (0), height (0), format (0), internal_format (0)
{
  if (!dummy)
	{
	  glGenTextures (1, &dummy);
	  glBindTexture (GL_TEXTURE_2D, dummy);

	  unsigned char empty[3] = {0, 0, 0};
	  glTexImage2D (GL_TEXTURE_2D, 0, 3, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, empty);
	}
  id = dummy;
}

void Texture::set_pixels (void *source, unsigned int bytes_per_row)
{
  typedef uint8_t byte_type;

  const byte_type *originalRaw = static_cast<byte_type *>(source);
  auto *flippedRaw = new byte_type[bytes_per_row * height];

  for (unsigned i = 0; i < height; ++i)
	{
	  const byte_type *srcBeg = originalRaw + (bytes_per_row * (height - i - 1));
	  const byte_type *srcEnd = srcBeg + bytes_per_row;

	  std::copy (srcBeg, srcEnd, flippedRaw + bytes_per_row * i);
	}
  size_t pixel_size = sizeof (byte_type) * bytes_per_row * height;
  pixels = malloc (pixel_size);
  memcpy (pixels, flippedRaw, pixel_size);
}

Texture::~Texture ()
{
  if (pixels) free (pixels);
}

void Texture::use ()
{
  glBindTexture (GL_TEXTURE_2D, id);
}

bool Texture::valid ()
{
  return id != dummy;
}
