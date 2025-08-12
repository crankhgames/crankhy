#pragma once
#include "ecs/ecs.h"
#include <array>
#include <unordered_map>

#include <iostream>

struct Transform
{
    float x, y;
};

struct Velocity
{
    float vX, vY;
};

struct Renderer
{
    const char *textureName;
};

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void print() = 0;
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
    void addComponent(EntityID entity, T component);

    /**
     * @brief Returns the component owned by entity of type T
     * @param entity entity's id
     * @return component owned by entity of type T
     */
    T &getComponent(EntityID entity);

    /**
     * @brief Destroys the component owned by entity (by id)
     * @param entity entity's id
     */
    void destroyComponent(EntityID entity);

    /**
     * @brief Prints out to the console the information about the component array
     */
    void print() override;
};

#include "ecs/component-array.inl"