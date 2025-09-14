#include "ecs/system-manager.h"
#include "game.h"
#include "debug.h"

void SystemManager::registerSystem(std::shared_ptr<System> system)
{
    debug::log("System  pushed with others systems");
    systems.push_back(system);
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
    ComponentBitset bitset = Game::get().getECSManager().getBitset(entity);
    for (int i = 0; i < systems.size(); i++)
    {
        System *system = systems[i].get();
        ComponentBitset systemBitset = system->getBitset();

        if ((bitset & systemBitset) == systemBitset && !system->hasEntity(entity))
        {
            system->addEntity(entity);
        }
    }
}

void SystemManager::entityDestroyed(EntityID entity)
{
    for (auto system : systems)
    {
        if (system->hasEntity(entity))
        {
            system->removeEntity(entity);
        }
    }
}