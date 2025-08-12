#pragma once
#include "ecs/system.h"

class SystemManager
{
private:
    std::vector<std::shared_ptr<System>> systems;
    std::vector<ComponentBitset> systemBitsets;

public:
    void registerSystem(std::shared_ptr<System> system, ComponentBitset systemBitset);
    void entityUpdated(EntityID entity);
    void entityDestroyed(EntityID entity);
    void tick(int deltaTime);
};