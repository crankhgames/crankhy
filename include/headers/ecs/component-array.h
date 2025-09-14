#pragma once
#include "ecs/ecs.h"
#include <array>
#include <unordered_map>

#include <iostream>

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void print() = 0;
    virtual bool hasEntity(EntityID entity) = 0;
    virtual void destroyComponent(EntityID entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
private:
    /**
     * @brief Array of components of type T
     */
    std::array<T, MAX_ENTITY_COUNT> components;

    /**
     * @brief Dictionnary that maps entity ids to component ids
     */
    std::unordered_map<EntityID, ComponentID> entity2Component;

    /**
     * @brief Dictionnary that maps component ids to entity ids
     */
    std::unordered_map<ComponentID, EntityID> component2Entity;

    ComponentID freeComponentID = 0;

public:
    /**
     * @brief Adds new component to this container based on entity's id
     * @param entity entity's id
     * @param component component of type T
     */
    void addComponent(EntityID entity, T component)
    {
        components[freeComponentID] = component;
        component2Entity[freeComponentID] = entity;
        entity2Component[entity] = freeComponentID;
        freeComponentID++;
    }

    /**
     * @brief Returns the component owned by entity of type T
     * @param entity entity's id
     * @return component owned by entity of type T
     */
    T &getComponent(EntityID entity)
    {
        // Checks if entity is present in entity pool
        assert(entity2Component.find(entity) != entity2Component.end());

        ComponentID componentID = entity2Component[entity];
        return components[componentID];
    }

    /**
     * @brief Destroys the component owned by entity (by id)
     * @param entity entity's id
     */
    void destroyComponent(EntityID entity)
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

    /**
     * @brief Checks if entity owns a component in this ComponentArray
     * @param entity entity's id
     * @return boolean
     */
    bool hasEntity(EntityID entity)
    {
        return entity2Component.find(entity) != entity2Component.end();
    }

    /**
     * @brief Prints out to the console the information about the component array
     */
    void print() override
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
};
