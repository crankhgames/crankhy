#pragma once

#include "SDL2/SDL.h"
#include "math/vector.h"
#include "graphics/sprite.h"

namespace Crankhy{

    struct TransformComponent
    {
        Vector position;
        Vector scale;
    };

    struct TextureRendererComponent
    {
        Sprite* sprite;
        
    };

    struct VelocityComponent
    {
        Vector velocity;
    };

    struct MoveOnInputComponent
    {
        SDL_Scancode up;
        SDL_Scancode down;
        SDL_Scancode left;
        SDL_Scancode right;
    };
}