#pragma once
#define SDL_MAIN_HANDLED
#undef main
#pragma warning( push)
#pragma warning(disable:26495 26812 26495) 

#include <SDL.h>

#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_render.h>

#include <SDL_main.h>
#pragma warning( pop )
#define SDL_MAIN_HANDLED
#undef main