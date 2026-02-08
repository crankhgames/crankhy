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
        bool collisionLayerMatrix[4][4] = {
            {true, true, true, true},
            {true, true, false, true},
            {true, false, true, true},
            {true, true, true, true},
        };
        Grid grid;

    public:
        CollisionSystem()
        {
            Game::get().getECS().addType2Bitset<TransformComponent>(systemBitset);
            Game::get().getECS().addType2Bitset<ColliderComponent>(systemBitset);
        }

        bool isColliding(EntityID entityA, EntityID entityB){
            
            ColliderComponent& colliderA = Game::get().getECS().getComponent<ColliderComponent>(entityA);
            ColliderComponent& colliderB = Game::get().getECS().getComponent<ColliderComponent>(entityB);

            if (!collisionLayerMatrix[(int)colliderA.layer][(int)colliderB.layer]){
                return false;
            }

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


            float leftA = transformA.position.x + colliderA.offset.x;
            float rightA = transformA.position.x + boundsA.x + colliderA.offset.x;
            float topA = transformA.position.y + colliderA.offset.y;
            float bottomA = transformA.position.y + boundsA.y + colliderA.offset.y;

            float leftB = transformB.position.x + colliderB.offset.x;
            float rightB = transformB.position.x + boundsB.x + colliderB.offset.x;
            float topB = transformB.position.y + colliderB.offset.y;
            float bottomB = transformB.position.y + boundsB.y + colliderB.offset.y;

            bool collided = !(leftA >= rightB || leftB >= rightA || topA >= bottomB || topB >= bottomA);

            if (!collided)
                return false;

            // Handle collisions
            if (colliderA.hasPhysicalPresence && colliderB.hasPhysicalPresence){

                if (SDL_min(SDL_fabsf(leftA - rightB), SDL_fabsf(leftB - rightA)) > SDL_min(SDL_fabsf(topA - bottomB), SDL_fabsf(bottomA - topB))){
                    if (SDL_fabsf(topA - bottomB) < SDL_fabsf(topB - bottomA)){
                        if (!colliderA.isStatic && !colliderB.isStatic){
                            transformA.position.y -= (topA - bottomB)/2;
                            transformB.position.y += (topA - bottomB)/2;
                        }
                        else if (!colliderA.isStatic){
                            transformA.position.y -= topA - bottomB;
                        }
                        else if (!colliderB.isStatic){
                            transformB.position.y += topA - bottomB;
                        }
                    }
                    else{
                        if (!colliderA.isStatic && !colliderB.isStatic){
                            transformA.position.y -= (bottomA - topB)/2;
                            transformB.position.y += (bottomA - topB)/2;
                        }
                        else if (!colliderA.isStatic){
                            transformA.position.y -= bottomA - topB;
                        }
                        else if (!colliderB.isStatic){
                            transformB.position.y += bottomA - topB;
                        }
                    }
                }
                else{
                    if (SDL_fabsf(leftA - rightB) < SDL_fabsf(leftB - rightA)){
                        if (!colliderA.isStatic && !colliderB.isStatic){
                            transformA.position.x += (rightB - leftA)/2;
                            transformB.position.x -= (rightB - leftA)/2;
                        }
                        else if (!colliderA.isStatic){
                            transformA.position.x += rightB - leftA;
                        }
                        else if (!colliderB.isStatic){
                            transformB.position.x -= rightB - leftA;
                        }
                    }
                    else{

                        if (!colliderA.isStatic && !colliderB.isStatic){
                            transformA.position.x += (leftB - rightA)/2;
                            transformB.position.x -= (leftB - rightA)/2;
                        }
                        else if (!colliderA.isStatic){
                            transformA.position.x += leftB - rightA;
                        }
                        else if (!colliderB.isStatic){
                            transformB.position.x -= leftB - rightA;
                        }
                    }
                }
            }

            return true;
        }

        bool isCollidingRectvsCircle(EntityID entityA, EntityID entityB){

            TransformComponent& transformA = Game::get().getECS().getComponent<TransformComponent>(entityA);
            TransformComponent& transformB = Game::get().getECS().getComponent<TransformComponent>(entityB);

            ColliderComponent& colliderA = Game::get().getECS().getComponent<ColliderComponent>(entityA);
            ColliderComponent& colliderB = Game::get().getECS().getComponent<ColliderComponent>(entityB);

            Vector bounds = std::get<RectCollisionInfo>(colliderA.shapeInfo).bounds;
            float radius = std::get<CircleCollisionInfo>(colliderB.shapeInfo).radius;

            float leftA = transformA.position.x + colliderA.offset.x;
            float rightA = transformA.position.x + bounds.x + colliderA.offset.x;
            float topA = transformA.position.y + colliderA.offset.y;
            float bottomA = transformA.position.y + bounds.y + colliderA.offset.y;

            Vector closestPoint = {
                SDL_max(leftA, SDL_min(transformB.position.x + colliderB.offset.x + radius, rightA)),
                SDL_max(topA, SDL_min(transformB.position.y + colliderB.offset.y + radius, bottomA)),
            };

            bool collided = (closestPoint - transformB.position - colliderB.offset - Vector(radius, radius)).lengthSquared() < radius * radius;

            if (!collided)
                return false;
            
            

            if (colliderA.hasPhysicalPresence && colliderB.hasPhysicalPresence){
                Vector diff = closestPoint - (transformB.position + Vector(radius, radius) + colliderB.offset);
                if (!colliderA.isStatic && !colliderB.isStatic){
                    transformA.position -= diff.normal() * (radius - diff.length()) / 2;
                    transformB.position += diff.normal() * (radius - diff.length()) / 2;
                }
                else if (!colliderA.isStatic){
                    transformA.position += diff.normal() * (radius - diff.length());
                }
                else if (!colliderB.isStatic){
                    transformB.position -= diff.normal() * (radius - diff.length());
                }
            }

            return true;

        }

        bool isCollidingCirclevsCircle(EntityID entityA, EntityID entityB){

            TransformComponent& transformA = Game::get().getECS().getComponent<TransformComponent>(entityA);
            TransformComponent& transformB = Game::get().getECS().getComponent<TransformComponent>(entityB);

            ColliderComponent& colliderA = Game::get().getECS().getComponent<ColliderComponent>(entityA);
            ColliderComponent& colliderB = Game::get().getECS().getComponent<ColliderComponent>(entityB);

            Vector diff = transformA.position + colliderA.offset - transformB.position - colliderB.offset;

            float distanceSquared = diff.lengthSquared();
            float sum_radii = std::get<CircleCollisionInfo>(colliderA.shapeInfo).radius + std::get<CircleCollisionInfo>(colliderB.shapeInfo).radius;
            bool collided = distanceSquared < SDL_powf(sum_radii, 2);
            
            if (!collided)
                return false;
            
            
            if (colliderA.hasPhysicalPresence && colliderB.hasPhysicalPresence){
                
                float length = sum_radii - diff.length();
                diff.normalize();
                diff *= length;
                

                if (!colliderA.isStatic && !colliderB.isStatic){
                    transformA.position += diff /2;
                    transformB.position -= diff /2;
                }
                else if (!colliderA.isStatic){
                    transformA.position += diff;
                }
                else if (!colliderB.isStatic){
                    transformB.position -= diff;
                }
            }

            
            return true;
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

                ColliderComponent& colliderEntity = Game::get().getECS().getComponent<ColliderComponent>(entity);
                TransformComponent& transformEntity = Game::get().getECS().getComponent<TransformComponent>(entity);

                if (colliderEntity.type == ColliderType::Rectangle){

                    Vector boundsA = std::get<RectCollisionInfo>(colliderEntity.shapeInfo).bounds;

                    EntityID cameraEntity = Game::get().getCamera();
                    TransformComponent& camTransform = Game::get().getECS().getComponent<TransformComponent>(cameraEntity);
                    CameraComponent& camComponent = Game::get().getECS().getComponent<CameraComponent>(cameraEntity);
                    SDL_Rect pos = localToScreen(camTransform, camComponent, transformEntity);
                    pos.x += colliderEntity.offset.x * camComponent.pixelsToUnit.x;
                    pos.y += colliderEntity.offset.y * camComponent.pixelsToUnit.y;
                    pos.w = boundsA.x * camComponent.pixelsToUnit.x;
                    pos.h = boundsA.y * camComponent.pixelsToUnit.y;

                    SDL_SetRenderDrawColor(Game::get().getWindow().renderer, 255, 0, 0, 255);
                    SDL_RenderDrawRect(Game::get().getWindow().renderer, &pos);

                }
                for (EntityID other : others){
                    if (entity >= other){
                        continue;
                    }
                    if (isColliding(entity, other)){
                        
                        debug::log("Handling collisions between ", entity, " & ", other, "!");
                    }
                }

            }
        }
    };

}