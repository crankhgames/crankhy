#pragma once
#include "ecs/system.h"
#include <memory>

class SystemManager
{
private:
    std::vector<std::shared_ptr<System>> systems;

public:
    /**
     * @brief Registers system into a list (vector) with other systems
     */
    void registerSystem(std::shared_ptr<System> system);

    /**
     * @brief If entity has been modified, calls entityUpdated
     */
    void entityUpdated(EntityID entity);

    /**
     * @brief Called when entity is destroyed and updates systems' entity set
     */
    void entityDestroyed(EntityID entity);

    /**
     * Executes the underlying logic of each system at each frame
     */
    void tick(int deltaTime);
};