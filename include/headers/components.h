#pragma once
#include "SDL2/SDL.h"
#include "math/vector.h"

struct Transform
{
    Vector position;
    Vector scale;
};

struct TextureRenderer
{
    SDL_Texture *texture;
};

struct Velocity
{
    Vector velocity;
};