#pragma once
#include "SDL.h"

SDL_Texture *loadTexture(const char *filename);
void draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);