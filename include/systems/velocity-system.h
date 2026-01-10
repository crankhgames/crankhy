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

    class VelocitySystem : public System
    {
    public:
        VelocitySystem()
        {
            Game::get().getECSManager().addType2Bitset<VelocityComponent>(systemBitset);
            Game::get().getECSManager().addType2Bitset<TransformComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                TransformComponent &eTransform = Game::get().getECSManager().getComponent<TransformComponent>(entity);
                VelocityComponent &eVelocity = Game::get().getECSManager().getComponent<VelocityComponent>(entity);

                eTransform.position += eVelocity.velocity * deltaTime;
            }
        }
    };
}