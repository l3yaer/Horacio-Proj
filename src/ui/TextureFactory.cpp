#include "TextureFactory.h"
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"

Texture *TextureFactory::create(const std::string &file)
{
    SDL_Surface *surface = IMG_Load(file.c_str());
    auto *texture = new Texture();

    if (surface == NULL) return texture;

    if (SDL_MUSTLOCK(surface))
    {
        SDL_LockSurface(surface);
    }

    setTextureFormat(&surface, texture);

    texture->height = surface->h;
    texture->width = surface->w;
    texture->set_pixels(surface->pixels, surface->pitch);

    texture->create();

    if (SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }

    SDL_FreeSurface(surface);

    return texture;
}

void TextureFactory::setTextureFormat(SDL_Surface **surface, Texture *texture)
{
    if ((*surface)->format->BytesPerPixel == 4)
    {
        if ((*surface)->format->Rmask == 0x000000ff)
        {
            texture->format = GL_RGBA;
            texture->internal_format = GL_RGBA8;
        } else
        {
            texture->format = GL_BGRA;
            texture->internal_format = GL_RGBA8;
        }
    } else if ((*surface)->format->BytesPerPixel == 3)
    {
        if ((*surface)->format->Rmask == 0x000000ff)
        {
            texture->format = GL_RGB;
            texture->internal_format = GL_RGB8;
        } else
        {
            texture->format = GL_BGR;
            texture->internal_format = GL_RGB8;
        }
    } else
    {
        SDL_PixelFormat *pformat = SDL_AllocFormat(SDL_PIXELFORMAT_BGR24);
        SDL_Surface *tmp = SDL_ConvertSurface((*surface), pformat, 0);
        texture->format = GL_BGR;
        texture->internal_format = GL_RGB8;
        if (SDL_MUSTLOCK((*surface)))
        {
            SDL_UnlockSurface((*surface));
        }
        SDL_FreeSurface((*surface));
        (*surface) = tmp;
        if (SDL_MUSTLOCK((*surface)))
        {
            SDL_LockSurface((*surface));
        }
    }
}

