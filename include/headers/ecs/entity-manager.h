#pragma once
#include "ecs/ecs.h"
#include <set>
#include <queue>

class EntityManager
{

private:
    /**
     * @brief Holds all the bitsets (each bit is set to 1 if owned or 0 if not owned by the entity) of each entity
     */
    std::unordered_map<EntityID, ComponentBitset> componentBitsets;

    std::queue<EntityID> deletedEntities;

    std::queue<EntityID> availableEntities;

public:
    /**
     * @brief ID for inexistant entities
     */
    EntityID nullEntity = -1;

    /**
     * @brief Creates an instance of EntityManager and generates avaiable entities
     */
    EntityManager();

    /**
     * @brief Adds new entity id to pool of existing entity
     * @return Id of created entity
     */
    EntityID createEntity();

    /**
     * @brief Removes id from existing entity pool
     * @param entity entity's id
     */
    void destroyEntity(EntityID entity);

    /**
     * @brief Checks if entity's id is present in pool of existing entity
     * @param entity entity's id
     * @return boolean
     */
    bool doesEntityExist(EntityID entity);

    /**
     * @brief Checks if entity owns a component of a certain type
     * @param entity entity's id
     * @param typeID type id of component
     */
    bool doesEntityOwnComponent(EntityID entity, ComponentTypeID typeID);

    /**
     * @brief Returns active entity count
     */
    int getEntityCount();

    /**
     * @brief Gets component bitset of entity
     * @param entity entity's id
     * @return component bitset
     */
    ComponentBitset &getBitset(EntityID entity);

    /**
     * @brief Checks if system includes this entity
     * @param entity entity's id
     * @param sysBitset system bitset
     */
    bool doesSystemBitContain(EntityID entity, ComponentBitset sysBitset);

    /**
     * @brief Deletes each "deleted" entity one by one by destroying every component it owns
     */
    void handleDestroyedEntities();
};
