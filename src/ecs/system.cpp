#include "ecs/system.h"
#include "game.h"

namespace Crankhy {

    void System::addEntity(EntityID entity)
    {
        if (hasEntity(entity))
            return;
        entities.push_back(entity);
    }

    void System::removeEntity(EntityID entity)
    {
        auto ptr = std::find(entities.begin(), entities.end(), entity);
        std::swap(*ptr, *(entities.end()-1));
        entities.pop_back();
    }

    bool System::hasEntity(EntityID entity)
    {
        return std::find(entities.begin(), entities.end(), entity) != entities.end();
    }
}