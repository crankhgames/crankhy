#pragma once
#include <memory>
#include "ecs/component-manager.h"
#include "ecs/entity-manager.h"
#include "ecs/system-manager.h"
#include "ecs/system.h"
#include "ecs/ecs.h"
#include "debug.h"

class ECSManager
{
private:
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;

public:
    ECSManager();

    // Creates entity by retrieving available entity ID
    EntityID createEntity();
    // Adds the EntityID to the deletedEntities pool to destroy at end of frame
    void destroyEntity(EntityID entity);

    ComponentBitset &getBitset(EntityID entity);

    template <typename T>
    void addComponent(EntityID entity, T component)
    {
        // Add component to component array through component manager
        componentManager->addComponent<T>(entity, component);

        // Update the component bitset of the entity
        addType2Bitset<T>(getBitset(entity));

        // Update systems, adds entity in their executing vector (list) if needed
        systemManager->entityUpdated(entity);
    }

    template <typename T>
    T &getComponent(EntityID entity)
    {
        return componentManager->getComponent<T>(entity);
    }

    template <typename T>
    void registerComponent()
    {
        componentManager->registerComponent<T>();
    }

    template <typename T>
    void addType2Bitset(ComponentBitset &bitset)
    {
        bitset[componentManager->getComponentTypeID<T>()] = 1;
    }

    /**
     * @brief Registers new System
     */
    void registerSystem(std::shared_ptr<System> system);

    /**
     * @brief Executes every frame
     */
    void tick(int deltatime);

    /**
     * @brief Calls ComponentManager and SystemManager to delete any info related to this entity id
     */
    void entityDestroyed(EntityID entity);
};