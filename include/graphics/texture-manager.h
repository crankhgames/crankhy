#pragma once
#include "SDL2/SDL.h"
#include "graphics/sprite.h"

namespace Crankhy {
    SDL_Texture *loadTexture(const char *filename);
    void draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);
    void draw(Sprite* sprite, SDL_Rect dest);
}