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

    class FollowSystem : public System
    {
    public:
        FollowSystem()
        {
            Game::get().getECS().addType2Bitset<TransformComponent>(systemBitset);
            Game::get().getECS().addType2Bitset<FollowComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                TransformComponent &eTransformComponent = Game::get().getECS().getComponent<TransformComponent>(entity);
                FollowComponent &eFollowComponent = Game::get().getECS().getComponent<FollowComponent>(entity);

                eTransformComponent.position = eFollowComponent.followedTransform->position + eFollowComponent.offset;
                debug::log("Follow ID : ", entity);
            }
        }
    };
}