#include "ecs/ecs-manager.h"
#include "debug/debug.h"

namespace Crankhy {

EntityID ECSManager::createEntity()
{
    return entityManager->createEntity();
}

void ECSManager::destroyEntity(EntityID entity)
{
    entityManager->destroyEntity(entity);
}

void ECSManager::tick(float deltatime)
{
    systemManager->tick(deltatime);
    entityManager->handleDestroyedEntities();
}

ComponentBitset &ECSManager::getBitset(EntityID entity)
{
    return entityManager->getBitset(entity);
}

void ECSManager::entityDestroyed(EntityID entity)
{
    systemManager->entityDestroyed(entity);
    componentManager->entityDestroyed(entity);
}

ECSManager::ECSManager()
{
    entityManager = std::make_unique<EntityManager>();
    componentManager = std::make_unique<ComponentManager>();
    systemManager = std::make_unique<SystemManager>();
}

void ECSManager::clearEntities(){
    entityManager->clearEntities();
}

}
