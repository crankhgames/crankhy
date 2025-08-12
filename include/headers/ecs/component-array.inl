#include "ecs/component-array.h"
#include <iostream>

template <typename T>
void ComponentArray<T>::addComponent(EntityID entity, T component)
{
    components[freeComponentID] = component;
    component2Entity[freeComponentID] = entity;
    entity2Component[entity] = freeComponentID;
    freeComponentID++;
}

template <typename T>
T &ComponentArray<T>::getComponent(EntityID entity)
{
    // Checks if entity is present in entity pool
    assert(entity2Component.find(entity) != entity2Component.end());

    ComponentID componentID = entity2Component[entity];
    return &components[componentID];
}

template <typename T>
void ComponentArray<T>::destroyComponent(EntityID entity)
{

    // Checks if entity is present in entity pool
    assert(entity2Component.find(entity) != entity2Component.end());

    ComponentID componentID = entity2Component[entity];

    // Swaps last entity with entity we want to delete to keep the data contiguous after deletion
    EntityID swappedEntity = component2Entity[freeComponentID - 1];

    std::swap(components[componentID], components[freeComponentID - 1]);
    entity2Component[swappedEntity] = componentID;
    component2Entity[componentID] = swappedEntity;

    // Erases/Deletes every info related to entity
    component2Entity.erase(freeComponentID - 1);
    entity2Component.erase(entity);
    --freeComponentID;
}

template <typename T>
void ComponentArray<T>::print()
{
    std::cout << "Component Array Type : " << typeid(T).name() << std::endl;
    std::cout << "Component Count : " << entity2Component.size() << std::endl;
    std::cout << "Entities:" << std::endl;
    for (auto const &pairInfo : entity2Component)
    {
        EntityID id = pairInfo.first;
        std::cout << id << ": " << entity2Component[id] << std::endl;
    }

    std::cout << std::endl;
}