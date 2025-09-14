#pragma once
#include "ecs/ecs.h"
#include <set>

// Executes the underlying logic on components based on their type
class System
{
protected:
    std::set<EntityID> entities;
    ComponentBitset systemBitset;

public:
    virtual void tick(int deltaTime) = 0;
    void addEntity(EntityID entity);
    bool hasEntity(EntityID entity);
    void removeEntity(EntityID entity);

    ComponentBitset getBitset() { return systemBitset; }
    ~System() = default;
};