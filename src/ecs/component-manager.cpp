#include "game.h"
#include "ecs/component-manager.h"
#include "debug.h"

void ComponentManager::print()
{
    debug::log("Component Type Count: ", getComponentTypeCount());

    // Prints every component array
    for (auto const &arr : componentArrays)
    {
        arr->print();
    }

    debug::log("Printed output successfully !");
}

ComponentTypeID ComponentManager::getComponentTypeCount()
{
    return static_cast<ComponentTypeID>(componentArrays.size());
}

void ComponentManager::entityDestroyed(EntityID entity)
{

    for (auto &array : componentArrays)
    {
        if (array->hasEntity(entity))
        {
            array->destroyComponent(entity);
        }
    }
}
