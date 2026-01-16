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

            RectColliderComponent& colliderA = std::get<RectColliderComponent>(Game::get().getECS().getComponent<ColliderComponent>(entityA));
            RectColliderComponent& colliderB = std::get<RectColliderComponent>(Game::get().getECS().getComponent<ColliderComponent>(entityB));



            float leftA = transformA.position.x;
            float rightA = transformA.position.x + colliderA.bounds.x;
            float topA = transformA.position.y;
            float bottomA = transformA.position.y + colliderA.bounds.y;

            float leftB = transformB.position.x;
            float rightB = transformB.position.x + colliderB.bounds.x;
            float topB = transformB.position.y;
            float bottomB = transformB.position.y + colliderB.bounds.y;

            bool collided = !(leftA >= rightB || leftB >= rightA || topA >= bottomB || topB >= bottomA);

            return collided;
        }

        bool isCollidingRectvsCircle(EntityID entityA, EntityID entityB){

            TransformComponent& transformA = Game::get().getECS().getComponent<TransformComponent>(entityA);
            TransformComponent& transformB = Game::get().getECS().getComponent<TransformComponent>(entityB);

            RectColliderComponent& colliderA = std::get<RectColliderComponent>(Game::get().getECS().getComponent<ColliderComponent>(entityA));
            CircleColliderComponent& colliderB = std::get<CircleColliderComponent>(Game::get().getECS().getComponent<ColliderComponent>(entityB));


            float leftA = transformA.position.x;
            float rightA = transformA.position.x + colliderA.bounds.x;
            float topA = transformA.position.y;
            float bottomA = transformA.position.y + colliderA.bounds.y;

            Vector closestPoint = {
                SDL_max(leftA, SDL_min(transformB.position.x, rightA)),
                SDL_max(topA, SDL_min(transformB.position.y, bottomA)),
            };

            bool collided = (closestPoint - transformB.position).lengthSquared() < colliderB.radius * colliderB.radius;

            return collided;

        }

        bool isCollidingCirclevsCircle(EntityID entityA, EntityID entityB){

            TransformComponent& transformA = Game::get().getECS().getComponent<TransformComponent>(entityA);
            TransformComponent& transformB = Game::get().getECS().getComponent<TransformComponent>(entityB);

            CircleColliderComponent& colliderA = std::get<CircleColliderComponent>(Game::get().getECS().getComponent<ColliderComponent>(entityA));
            CircleColliderComponent& colliderB = std::get<CircleColliderComponent>(Game::get().getECS().getComponent<ColliderComponent>(entityB));

            float distanceSquared = (transformA.position - transformB.position).lengthSquared();
            return distanceSquared > SDL_powf(colliderA.radius + colliderB.radius, 2);
        }

        void addEntity(EntityID entity) override{
            System::addEntity(entity);
            ColliderComponent& collider = Game::get().getECS().getComponent<ColliderComponent>(entity);
            grid.addEntity(entity);
            
            if (std::holds_alternative<RectColliderComponent>(collider)){
                debug::log("Entity ", entity, " has a collider of type Rectangle");
                colliderTypes[entity] = ColliderType::Rectangle;
            }
            else if (std::holds_alternative<CircleColliderComponent>(collider)){
                debug::log("Entity ", entity, " has a collider of type Circle");
                colliderTypes[entity] = ColliderType::Circle;
            }
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