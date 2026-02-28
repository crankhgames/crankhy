#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

// Game scripts / managers
#include "math/vector.h"
#include "graphics/texture-manager.h"

// SDL header files
#include "SDL2/SDL.h"

#include "debug.h"

namespace Crankhy{

    class FollowBehaviourSystem : public System
    {
    public:
        FollowBehaviourSystem()
        {
            Game::get().getECS().addType2Bitset<TransformComponent>(systemBitset);
            Game::get().getECS().addType2Bitset<FollowBehaviourComponent>(systemBitset);
            Game::get().getECS().addType2Bitset<VelocityComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                TransformComponent &eTransformComponent = Game::get().getECS().getComponent<TransformComponent>(entity);
                FollowBehaviourComponent &eFollowComponent = Game::get().getECS().getComponent<FollowBehaviourComponent>(entity);
                VelocityComponent &eVelocityComponent = Game::get().getECS().getComponent<VelocityComponent>(entity);
                
                Vector dir = eFollowComponent.followedTransform->position - eTransformComponent.position;

                eVelocityComponent.velocity = dir.normal() * eFollowComponent.speed;

            }
        }
    };
}