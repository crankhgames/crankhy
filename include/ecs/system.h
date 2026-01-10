#pragma once
#include "ecs/ecs.h"
#include <set>

namespace Crankhy {

    // Executes the underlying logic on components based on their type
    class System
    {
    protected:
        std::set<EntityID> entities;
        ComponentBitset systemBitset;

    public:
        virtual void tick(float deltaTime) = 0;
        virtual void addEntity(EntityID entity);
        bool hasEntity(EntityID entity);
        virtual void removeEntity(EntityID entity);

        ComponentBitset getBitset() { return systemBitset; }
        ~System() = default;
    };
}