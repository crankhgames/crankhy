#include "ecs/entity-manager.h"
#include "debug.h"
#include "game.h"

// Entity Manager Method Definitions

EntityID EntityManager::createEntity()
{
    if (getEntityCount() >= MAX_ENTITY_COUNT)
    {
        debug::warning("Entity Count Overflow...");
        return nullEntity;
    }

    componentBitsets[newEntityID] = ComponentBitset();
    return newEntityID++;
}

void EntityManager::destroyEntity(EntityID entity)
{
    assert(doesEntityExist(entity) && "This Entity ID doesn't exist !");
    deletedEntities.push(entity);
}

ComponentBitset EntityManager::getBitset(EntityID entity)
{
    assert(doesEntityExist(entity) && "This Entity ID doesn't exist !");
    return componentBitsets[entity];
}

bool EntityManager::doesEntityExist(EntityID entity)
{
    return componentBitsets.find(entity) != componentBitsets.end();
}

int EntityManager::getEntityCount()
{
    return componentBitsets.size();
}

void EntityManager::handleDestroyedEntities()
{
    for (; !deletedEntities.empty(); deletedEntities.pop())
    {
        EntityID deletedEntity = deletedEntities.front();
        componentBitsets.erase(deletedEntity);
        Game::get()->getComponentManager()->entityDestroyed(deletedEntity);
        Game::get()->getSystemManager()->entityDestroyed(deletedEntity);
    }
}

bool EntityManager::doesEntityOwnComponent(EntityID entity, ComponentTypeID typeID)
{
    return componentBitsets[entity][typeID];
}