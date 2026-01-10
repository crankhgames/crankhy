#pragma once

#include "SDL2/SDL.h"
#include "math/vector.h"
#include "graphics/sprite.h"

#include <variant>

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

    enum class ColliderType{
        None,
        Rectangle,
        Circle
    };



    struct CircleColliderComponent{
        float radius;
        bool isStatic;

        ColliderType type = ColliderType::Circle;

    };

    struct RectColliderComponent{
        Vector bounds;
        bool isStatic;

        ColliderType type = ColliderType::Rectangle;

    };


    using ColliderComponent = std::variant<RectColliderComponent, CircleColliderComponent>;

}