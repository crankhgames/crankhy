#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

#include "debug.h"

namespace Crankhy{
        

    class BulletCollisionSystem : public System
    {
        public:
            BulletCollisionSystem()
            {
                Game::get().getECS().addType2Bitset<ColliderComponent>(systemBitset);
            }

            void tick(float deltaTime) override
            {
                for (EntityID entity : entities)
                {
                    ColliderComponent& c = Game::get().getECS().getComponent<ColliderComponent>(entity);

                    if (c.layer != CollisionLayer::LAYER_BULLET){
                        continue;
                    }

                    debug::log("Collider in contact: ", c.collidedEntities.size());
                    
                    for (auto& other : c.collidedEntities) {

                        debug::log("Collided with ", other);
                        if (Game::get().getECS().getComponent<ColliderComponent>(other).layer == CollisionLayer::LAYER_ENEMY){

                            Game::get().getECS().destroyEntity(other);
                        }
                    }

                    if (c.collidedEntities.size() > 0) {
                        Game::get().getECS().destroyEntity(entity);
                    }
                    
                    //for (EntityID other : c.collidedEntities){
                        //if
                    //}
                }
            }
        };
}