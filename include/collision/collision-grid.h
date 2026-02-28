#pragma once

#include "ecs/system.h"

#include <vector>
#include <unordered_map>
#include <array>
#include "scene/components.h"

namespace Crankhy{


    struct EntityCollisionInfo{
        int xidx, yidx;
        bool isStatic;
    };

    class Grid{
    public:

        static const int width = 100;
        static const int height = 100;
        static const int cellSize = 2; 

        Grid() = default;
        ~Grid() = default;

        void addEntity(EntityID entity);
        void updateEntity(EntityID entity);
        void removeEntity(EntityID entity);

        std::pair<int, int> getIndexPos(TransformComponent& transform);

        std::vector<EntityID> getNeighbors(EntityID entity);

    private:
        std::array<std::array<std::vector<EntityID>, height/cellSize>, width/cellSize> cells;
        std::unordered_map<EntityID, EntityCollisionInfo> collisionInfo;
    };

}