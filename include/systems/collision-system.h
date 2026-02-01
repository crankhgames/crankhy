#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

// Game scripts / managers
#include "math/vector.h"
#include "graphics/texture-manager.h"
#include "input/input.h"
#include "collision/collision-grid.h"

// SDL header files
#include "SDL2/SDL.h"

#include "debug.h"

namespace Crankhy{ 


    class CollisionSystem : public System
    {
    private:
        std::unordered_map<EntityID, ColliderType> colliderTypes;
        Grid grid;

    public:
        CollisionSystem()
        {
            Game::get().getECS().addType2Bitset<TransformComponent>(systemBitset);
            Game::get().getECS().addType2Bitset<ColliderComponent>(systemBitset);
        }

        bool isColliding(EntityID entityA, EntityID entityB){
            if (colliderTypes[entityA] == ColliderType::Rectangle && colliderTypes[entityB] == ColliderType::Rectangle){
                return isCollidingRectvsRect(entityA, entityB);
            }
            if (colliderTypes[entityA] == ColliderType::Rectangle && colliderTypes[entityB] == ColliderType::Circle){
                return isCollidingRectvsCircle(entityA, entityB);
            }
            if (colliderTypes[entityA] == ColliderType::Circle && colliderTypes[entityB] == ColliderType::Circle){
                return isCollidingCirclevsCircle(entityA, entityB);
            }
            if (colliderTypes[entityA] == ColliderType::Circle && colliderTypes[entityB] == ColliderType::Rectangle){
                return isCollidingRectvsCircle(entityB, entityA);
            }
            return false;
        }

        bool isCollidingRectvsRect(EntityID entityA, EntityID entityB){
            TransformComponent& transformA = Game::get().getECS().getComponent<TransformComponent>(entityA);
            TransformComponent& transformB = Game::get().getECS().getComponent<TransformComponent>(entityB);

            ColliderComponent& colliderA = Game::get().getECS().getComponent<ColliderComponent>(entityA);
            ColliderComponent& colliderB = Game::get().getECS().getComponent<ColliderComponent>(entityB);

            Vector boundsA = std::get<RectCollisionInfo>(colliderA.shapeInfo).bounds;
            Vector boundsB = std::get<RectCollisionInfo>(colliderB.shapeInfo).bounds;


            float leftA = transformA.position.x;
            float rightA = transformA.position.x + boundsA.x;
            float topA = transformA.position.y;
            float bottomA = transformA.position.y + boundsA.y;

            float leftB = transformB.position.x;
            float rightB = transformB.position.x + boundsB.x;
            float topB = transformB.position.y;
            float bottomB = transformB.position.y + boundsB.y;

            bool collided = !(leftA >= rightB || leftB >= rightA || topA >= bottomB || topB >= bottomA);

            return collided;
        }

        bool isCollidingRectvsCircle(EntityID entityA, EntityID entityB){

            TransformComponent& transformA = Game::get().getECS().getComponent<TransformComponent>(entityA);
            TransformComponent& transformB = Game::get().getECS().getComponent<TransformComponent>(entityB);

            ColliderComponent& colliderA = Game::get().getECS().getComponent<ColliderComponent>(entityA);
            ColliderComponent& colliderB = Game::get().getECS().getComponent<ColliderComponent>(entityB);

            Vector bounds = std::get<RectCollisionInfo>(colliderA.shapeInfo).bounds;
            float radius = std::get<CircleCollisionInfo>(colliderB.shapeInfo).radius;

            float leftA = transformA.position.x;
            float rightA = transformA.position.x + bounds.x;
            float topA = transformA.position.y;
            float bottomA = transformA.position.y + bounds.y;

            Vector closestPoint = {
                SDL_max(leftA, SDL_min(transformB.position.x, rightA)),
                SDL_max(topA, SDL_min(transformB.position.y, bottomA)),
            };

            return (closestPoint - transformB.position).lengthSquared() < radius * radius;

        }

        bool isCollidingCirclevsCircle(EntityID entityA, EntityID entityB){

            TransformComponent& transformA = Game::get().getECS().getComponent<TransformComponent>(entityA);
            TransformComponent& transformB = Game::get().getECS().getComponent<TransformComponent>(entityB);

            ColliderComponent& colliderA = Game::get().getECS().getComponent<ColliderComponent>(entityA);
            ColliderComponent& colliderB = Game::get().getECS().getComponent<ColliderComponent>(entityB);

            float distanceSquared = (transformA.position - transformB.position).lengthSquared();
            float sum_radii = std::get<CircleCollisionInfo>(colliderA.shapeInfo).radius + std::get<CircleCollisionInfo>(colliderB.shapeInfo).radius;
            return distanceSquared > SDL_powf(sum_radii, 2);
        }

        void addEntity(EntityID entity) override{
            System::addEntity(entity);
            ColliderComponent& collider = Game::get().getECS().getComponent<ColliderComponent>(entity);
            grid.addEntity(entity);
            colliderTypes[entity] = collider.type;
        }

        void removeEntity(EntityID entity) override{
            System::removeEntity(entity);
            colliderTypes.erase(entity);
            grid.removeEntity(entity);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                grid.updateEntity(entity);
                std::vector<EntityID> others = grid.getNeighbors(entity);

                for (EntityID other : others){
                    if (entity >= other){
                        continue;
                    }
                    if (isColliding(entity, other)){
                        debug::log(SDL_GetTicks(), " Collision !");
                    }
                }

            }
        }
    };

}