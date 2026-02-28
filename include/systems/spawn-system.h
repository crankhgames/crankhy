#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

#include "debug.h"

namespace Crankhy{
        

    class SpawnSystem : public System
    {
        public:
            SpawnSystem()
            {
                Game::get().getECS().addType2Bitset<TransformComponent>(systemBitset);
                Game::get().getECS().addType2Bitset<SpawnerComponent>(systemBitset);
            }

            void tick(float deltaTime) override
            {
                for (EntityID entity : entities)
                {
                    TransformComponent &transform = Game::get().getECS().getComponent<TransformComponent>(entity);
                    SpawnerComponent& spawner = Game::get().getECS().getComponent<SpawnerComponent>(entity);

                    spawner.counter += deltaTime;

                    if (spawner.counter < spawner.delayBtwSpawns){
                        continue;
                    }

                    spawner.counter = 0;

                    spawner.spawnFunc(transform.position.x, transform.position.y, spawner.player);

                }
            }
        };
}