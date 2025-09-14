#include "ecs/ecs-manager.h"
#include "debug.h"

EntityID ECSManager::createEntity()
{
    return entityManager->createEntity();
}

void ECSManager::destroyEntity(EntityID entity)
{
    entityManager->destroyEntity(entity);
}

void ECSManager::registerSystem(std::shared_ptr<System> system)
{
    debug::log("System is registering...");
    systemManager->registerSystem(system);
}

void ECSManager::tick(int deltatime)
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
    componentManager->entityDestroyed(entity);
    systemManager->entityDestroyed(entity);
}

ECSManager::ECSManager()
{
    entityManager = std::make_unique<EntityManager>();
    componentManager = std::make_unique<ComponentManager>();
    systemManager = std::make_unique<SystemManager>();
}
