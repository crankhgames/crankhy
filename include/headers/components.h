#pragma once
#include "SDL.h"

struct Transform
{
    int x, y;
    int scaleX, scaleY;
};

struct Renderer
{
    SDL_Texture *texture;
};

struct Velocity
{
    int velX, velY;
};