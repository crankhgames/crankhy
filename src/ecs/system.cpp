#include "ecs/system.h"

void System::addEntity(EntityID entity)
{
    entities.insert(entity);
}

void System::removeEntity(EntityID entity)
{
    entities.erase(entity);
}

bool System::hasEntity(EntityID entity)
{
    return entities.find(entity) != entities.end();
}