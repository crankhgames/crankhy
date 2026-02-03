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

    struct ShooterComponent{
        float bulletSpeed;
        float delayBtwShots;
        float counter;
    };


    enum class ColliderType{
        None,
        Rectangle,
        Circle
    };

    struct CircleCollisionInfo{
        float radius;
    };

    struct RectCollisionInfo{
        Vector bounds;
    };

    using ShapeCollisionInfo = std::variant<CircleCollisionInfo, RectCollisionInfo>;

    struct ColliderComponent{
        ColliderType type;
        //std::string tag;
        bool isStatic;
        ShapeCollisionInfo shapeInfo;
    };
}