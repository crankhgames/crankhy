#pragma once

#include "SDL2/SDL.h"
#include "math/vector.h"
#include "graphics/sprite.h"

#include <variant>
#include <memory>

namespace Crankhy{

    struct TransformComponent
    {
        Vector position;
        Vector scale;

    };

    struct FollowComponent{
        TransformComponent* followedTransform;
        Vector offset;
    };

    struct TextureRendererComponent
    {
        Spritesheet* sprite;
        bool flipX = false;
        bool flipY = false;
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

    struct AnimationRendererComponent{
        
        int startFrame;
        int endFrame;
        
        float nextFrameCounter;

        float counter = 0;
        int currentFrame = 0;


    };


    struct CameraComponent{
        Vector pixelsToUnit;
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