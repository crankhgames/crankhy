#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

// SDL header files
#include "SDL2/SDL.h"

#include "debug.h"

namespace Crankhy{ 


    class LifetimeSystem : public System
    {
    public:
        LifetimeSystem()
        {
            Game::get().getECS().addType2Bitset<LifetimeComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                LifetimeComponent &eLifetime = Game::get().getECS().getComponent<LifetimeComponent>(entity);
                eLifetime.counter += deltaTime;

                if (eLifetime.counter >= eLifetime.totalLifetime){
                    Game::get().getECS().destroyEntity(entity);
                }
            }
        }
    };

}