#include "ecs/system.h"

void System::addEntity(EntityID entity)
{
    entities.insert(entity);
}

void System::removeEntity(EntityID entity)
{
    if (entities.find(entity) != entities.end())
    {
        entities.erase(entity);
    }
}
