#pragma once
#include "ecs/ecs.h"
#include <set>

class System
{
private:
    std::set<EntityID> entities;

public:
    virtual void tick(int deltaTime) = 0;
    void addEntity(EntityID entity);
    void removeEntity(EntityID entity);
    ~System() = default;
};