#pragma once

#include "ecs/system.h"

#include <vector>
#include <unordered_map>
#include <array>

namespace Crankhy{


    struct EntityCollisionInfo{
        int xidx, yidx;
        bool isStatic;
    };

    class Grid{
    private:
        static const int width = 800;
        static const int height = 600;
        static const int cellSize = 100;

        std::array<std::array<std::vector<EntityID>, height/cellSize>, width/cellSize> cells;
        std::unordered_map<EntityID, EntityCollisionInfo> collisionInfo;
        
    public:
        Grid() = default;
        ~Grid() = default;

        void addEntity(EntityID entity);
        void updateEntity(EntityID entity);
        void removeEntity(EntityID entity);


        std::vector<EntityID> getNeighbors(EntityID entity);

    };

}