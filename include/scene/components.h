#pragma once

#include "SDL2/SDL.h"
#include "math/vector.h"
#include "graphics/sprite.h"
#include "animation/animation.h"
#include "ecs/ecs.h"

#include <variant>
#include <memory>
#include <string>
#include <functional>

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
        AnimationManager* animation;
    };


    struct CameraComponent{
        Vector pixelsToUnit;
    };

    struct ShooterComponent{
        float bulletSpeed;
        float delayBtwShots;
        float counter;
    };


    struct LifetimeComponent{
        float totalLifetime;
        float counter = 0.f;
    };


#pragma region Collision Related Components
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

    enum class CollisionLayer{
        LAYER_NONE,
        LAYER_PLAYER,
        LAYER_BULLET,
        LAYER_BLOCK,
        LAYER_ENEMY
    };

    struct ColliderComponent{
        ColliderType type;
        CollisionLayer layer;
        bool isStatic=false;
        bool hasPhysicalPresence=true;
        Vector offset;
        ShapeCollisionInfo shapeInfo;
        std::vector<EntityID> collidedEntities;
    };

#pragma endregion


struct FollowBehaviourComponent{
    TransformComponent* followedTransform;
    float speed;
};

struct SpawnerComponent{
    float delayBtwSpawns;
    std::function<void(float, float, EntityID)> spawnFunc;
    EntityID player;
    float counter = 0.f;
};

}