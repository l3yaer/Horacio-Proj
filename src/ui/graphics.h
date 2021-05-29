#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include <types.h>

#ifdef _OS_DARWIN
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>
#endif

#ifdef _OS_WIN
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>
#endif

#ifdef _OS_LINUX
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>
#endif

#endif //_GRAPHICS_H_
