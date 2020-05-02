#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_

#include <string>

class Texture;

struct SDL_Surface;

class TextureFactory
{
public:

    static Texture *create(const std::string &file);

private:

    static void setTextureFormat(SDL_Surface **, Texture *);

};


#endif //TEXTUREFACTORY_H_
