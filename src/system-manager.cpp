#include "ecs/system-manager.h"
#include "game.h"

void SystemManager::registerSystem(std::shared_ptr<System> system, ComponentBitset systemBitset)
{
    systems.push_back(system);
    systemBitsets.push_back(systemBitset);
}

void SystemManager::tick(int deltaTime)
{
    for (auto system : systems)
    {
        system->tick(deltaTime);
    }
}

void SystemManager::entityUpdated(EntityID entity)
{
    ComponentBitset bitset = Game::get()->getEntityManager()->getBitset(entity);
    for (int i = 0; i < systems.size(); i++)
    {
        ComponentBitset systemBitset = systemBitsets[i];
        System *system = systems[i].get();

        if ((bitset & systemBitset) == systemBitset)
        {
            system->addEntity(entity);
        }
        else
        {
            system->removeEntity(entity);
        }
    }
}

void SystemManager::entityDestroyed(EntityID entity)
{
    for (auto system : systems)
    {
        system->removeEntity(entity);
    }
}