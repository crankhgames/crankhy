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
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        ComponentTypeID typeId = getComponentTypeID<T>();
        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeId]);
    }

public:
    /**
     * @brief Get Component Type name based on type of component T
     * @tparam T component type
     * @return ComponentType (const char *) type of component
     */
    template <typename T>
    ComponentType getComponentType()
    {
        return static_cast<ComponentType>(typeid(T).name());
    }

    /**
     * @brief Get Component Type ID based on type of component T
     * @tparam T component type
     * @return ComponentTypeID (size_t) type of component
     */
    template <typename T>
    ComponentTypeID getComponentTypeID()
    {
        return componentTypeName2ID[getComponentType<T>()];
    }

    /**
     * @brief Get the number of types registered in the component manager
     * @return number of component arrays
     */
    ComponentTypeID getComponentTypeCount();

    /**
     * @brief Adds a new component to an entity based on it's id
     * @tparam T component type
     * @param entity entity's id
     * @param component component of type T
     */
    template <typename T>
    void addComponent(EntityID entity, T component)
    {
        getComponentArray<T>()->addComponent(entity, component);
    }

    /**
     * @brief Gets the component of an entity based on the component and entity's id
     * @tparam T component type
     * @param entity entity's id
     * @return component owned by entity
     */
    template <typename T>
    T &getComponent(EntityID entity)
    {
        return getComponentArray<T>()->getComponent(entity);
    }

    void entityDestroyed(EntityID entity);

    /**
     * @brief Registers new Component type and creates a new container for that new component type
     * @tparam T component type
     */
    template <typename T>
    void registerComponent()
    {
        componentTypeName2ID[getComponentType<T>()] = getComponentTypeCount();
        componentArrays.push_back(std::make_shared<ComponentArray<T>>());
    }

    /**
     * @brief Prints out to the console information about the component manager (component types)
     */
    void print();
};
