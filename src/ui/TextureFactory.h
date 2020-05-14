#ifndef _TEXTUREFACTORY_H_
#define _TEXTUREFACTORY_H_

#include <string>

class Texture;

struct SDL_Surface;

class TextureFactory
{
 public:

  static Texture *create (const std::string &file);

 private:

  static void setTextureFormat (SDL_Surface **, Texture *);

};

#endif //_TEXTUREFACTORY_H_
