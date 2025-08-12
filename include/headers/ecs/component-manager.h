#pragma once
#include "ecs/ecs.h"
#include "ecs/component-array.h"
#include <memory>
#include <unordered_map>
#include <vector>

class ComponentManager
{
private:
    /**
     * @brief Holds every component array by type
     */
    std::vector<std::shared_ptr<IComponentArray>> componentArrays;

    /**
     * @brief Dictionnary that links the Component Type (const char *) to the Component Type ID (size_t), index of the componentArrays
     */
    std::unordered_map<ComponentType, ComponentTypeID> componentTypeName2ID;

    /**
     * @brief Gets the according component container based on the component's type
     * @return shared pointer pointing to the address of the component array
     */
    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray();

public:
    /**
     * @brief Get Component Type name based on type of component T
     * @tparam T component type
     * @return ComponentType (const char *) type of component
     */
    template <typename T>
    ComponentType getComponentType();

    /**
     * @brief Get Component Type ID based on type of component T
     * @tparam T component type
     * @return ComponentTypeID (size_t) type of component
     */
    template <typename T>
    ComponentTypeID getComponentTypeID();

    /**
     * @brief Get the number of types registered in the component manager
     * @return number of component arrays
     */
    ComponentTypeID getComponentTypeCount();

    /**
     * @brief Adds component type to bitset
     * @param bitset reference to bitset
     */
    template <typename T>
    void addComponentTypeToBitset(ComponentBitset &bitset);

    /**
     * @brief Adds a new component to an entity based on it's id
     * @tparam T component type
     * @param entity entity's id
     * @param component component of type T
     */
    template <typename T>
    void addComponent(EntityID entity, T component);

    /**
     * @brief Gets the component of an entity based on the component and entity's id
     * @tparam T component type
     * @param entity entity's id
     * @return component owned by entity
     */
    template <typename T>
    T &getComponent(EntityID entity);

    /**
     * @brief Destroys/Remove/Delete component of an entity based on it's id
     * @tparam T component type
     * @param entity entity's id
     */
    template <typename T>
    void destroyComponent(EntityID entity);

    void entityDestroyed(EntityID entity);

    /**
     * @brief Registers new Component type and creates a new container for that new component type
     * @tparam T component type
     */
    template <typename T>
    void registerComponent();

    /**
     * @brief Prints out to the console information about the component manager (component types)
     */
    void print();
};

#include "ecs/component-manager.inl"
