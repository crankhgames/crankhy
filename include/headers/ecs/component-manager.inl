#include "game.h"
#include "ecs/component-manager.h"
#include "debug.h"

template <typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::getComponentArray()
{
    ComponentTypeID typeID = getComponentTypeID<T>();
    return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeID]);
}

template <typename T>
ComponentType ComponentManager::getComponentType()
{
    return static_cast<ComponentType>(typeid(T).name());
}

template <typename T>
ComponentTypeID ComponentManager::getComponentTypeID()
{
    return componentTypeName2ID[getComponentType<T>()];
}

template <typename T>
void ComponentManager::addComponent(EntityID entity, T component)
{
    getComponentArray<T>()->addComponent(entity, component);
    Game::get()->getEntityManager()->getComponentBitset(entity)[getComponentTypeID<T>()] = 1;
    Game::get()->getSystemManager()->entityUpdated(entity);
}

template <typename T>
T &ComponentManager::getComponent(EntityID entity)
{
    return getComponentArray<T>()->getComponent(entity);
}

template <typename T>
void ComponentManager::destroyComponent(EntityID entity)
{
    getComponentArray<T>()->destroyComponent(entity);
    Game::Get()->getEntityManager()->getComponentBitset(entity)[getComponentTypeID<T>()] = 0;
}

void ComponentManager::entityDestroyed(EntityID entity)
{
    for (ComponentTypeID i = 0; i < componentArrays.size(); i++)
    {
        if (Game::get()->getEntityManager()->doesEntityOwnComponent(entity, i))
        {
            componentArrays[i]->destroyComponent(entity);
        }
    }
}

template <typename T>
void ComponentManager::registerComponent()
{
    componentTypeName2ID.insert({getComponentType<T>(), getComponentTypeCount()});
    componentArrays.push_back(std::make_shared<ComponentArray<T>>());
}

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

template <typename T>
void ComponentManager::addComponentTypeToBitset(ComponentBitset &bitset)
{
    bitset[getComponentTypeID<T>()] = 1;
}