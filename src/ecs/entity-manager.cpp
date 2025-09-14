#include "ecs/entity-manager.h"
#include "debug.h"
#include "game.h"

// Entity Manager Method Definitions

EntityManager::EntityManager()
{

    for (EntityID i = 0; i < MAX_ENTITY_COUNT; i++)
    {
        availableEntities.push(i);
    }
}

EntityID EntityManager::createEntity()
{
    if (availableEntities.empty())
    {
        debug::warning("Entity Count Overflow...");
        return nullEntity;
    }

    // Request a new ID for entities
    EntityID requestedID = availableEntities.front();
    availableEntities.pop();

    componentBitsets[requestedID] = ComponentBitset();
    return requestedID;
}

void EntityManager::destroyEntity(EntityID entity)
{
    assert(doesEntityExist(entity) && "This Entity ID doesn't exist !");
    deletedEntities.push(entity);
}

ComponentBitset &EntityManager::getBitset(EntityID entity)
{
    assert(doesEntityExist(entity) && "This Entity ID doesn't exist !");
    return componentBitsets[entity];
}

bool EntityManager::doesEntityExist(EntityID entity)
{
    return entity != nullEntity && componentBitsets.find(entity) != componentBitsets.end();
}

int EntityManager::getEntityCount()
{
    return componentBitsets.size();
}

bool EntityManager::doesEntityOwnComponent(EntityID entity, ComponentTypeID typeID)
{
    return componentBitsets[entity][typeID];
}

bool EntityManager::doesSystemBitContain(EntityID entity, ComponentBitset sysBitset)
{
    return (getBitset(entity) & sysBitset) == sysBitset;
}

void EntityManager::handleDestroyedEntities()
{
    for (; !deletedEntities.empty(); deletedEntities.pop())
    {
        EntityID deletedEntity = deletedEntities.front();
        Game::get().getECSManager().entityDestroyed(deletedEntity);
        availableEntities.push(deletedEntity);
    }
}