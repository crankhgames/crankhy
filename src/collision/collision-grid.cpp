#include "collision/collision-grid.h"
#include "scene/components.h"
#include "game.h"

namespace Crankhy{

    void Grid::addEntity(EntityID entity){
        TransformComponent& transform = Game::get().getECS().getComponent<TransformComponent>(entity);
        ColliderComponent& collider = Game::get().getECS().getComponent<ColliderComponent>(entity);


        int xidx = transform.position.x / cellSize;
        int yidx = transform.position.y / cellSize;

        debug::log(xidx, "; ",yidx);
        
        cells[xidx][yidx].push_back(entity);
        collisionInfo.emplace(std::pair<EntityID, EntityCollisionInfo>(
            entity,
            EntityCollisionInfo {
                xidx, yidx,
                false
            }
        ));

    }

    void Grid::removeEntity(EntityID entity){
        TransformComponent& transform = Game::get().getECS().getComponent<TransformComponent>(entity);

        int xidx = transform.position.x / cellSize;
        int yidx = transform.position.y / cellSize;
        
        auto it = std::find(cells[xidx][yidx].begin(), cells[xidx][yidx].end(), entity);
        
        if (cells[xidx][yidx].size() > 0 && it != cells[xidx][yidx].end()){
            std::swap(*it, *(cells[xidx][yidx].end() - 1));
            cells[xidx][yidx].pop_back();
            if (collisionInfo.find(entity) != collisionInfo.end()){
                collisionInfo.erase(entity);
            }
        }
    }

    void Grid::updateEntity(EntityID entity){
        EntityCollisionInfo& entColInfo = collisionInfo.at(entity);
        if (entColInfo.isStatic){
            return;
        }

        
        TransformComponent& transform = Game::get().getECS().getComponent<TransformComponent>(entity);

        int xidx = transform.position.x / cellSize;
        int yidx = transform.position.y / cellSize;

        if (entColInfo.xidx != xidx || entColInfo.yidx != yidx){

            auto it = std::find(cells[entColInfo.xidx][entColInfo.yidx].begin(), cells[entColInfo.xidx][entColInfo.yidx].end(), entity);

            if (it != cells[entColInfo.xidx][entColInfo.yidx].end()){
                std::swap(*it, *(cells[entColInfo.xidx][entColInfo.yidx].end() - 1));
                cells[entColInfo.xidx][entColInfo.yidx].pop_back();
            }


            entColInfo.xidx = xidx;
            entColInfo.yidx = yidx;

            cells[xidx][yidx].push_back(entity);
        }

    }

    std::vector<EntityID> Grid::getNeighbors(EntityID entity){
        
        EntityCollisionInfo entCollisionInfo = collisionInfo[entity];
        int xidx = entCollisionInfo.xidx;
        int yidx = entCollisionInfo.yidx;
        std::vector<EntityID> result = cells[xidx][yidx];
        bool onLeftSide = xidx == 0;
        bool onRightSide = xidx == width/cellSize-1;
        bool onTopSide = yidx == 0;
        bool onBottomSide = yidx == height/cellSize-1;
        
        if (!onLeftSide){
            result.insert(result.end(), cells[xidx-1][yidx].begin(), cells[xidx-1][yidx].end());
            if (!onTopSide){
                result.insert(result.end(), cells[xidx-1][yidx-1].begin(), cells[xidx-1][yidx-1].end());
            }
            if (!onBottomSide){
                result.insert(result.end(), cells[xidx-1][yidx+1].begin(), cells[xidx-1][yidx+1].end());
            }
        }

        if (!onRightSide){
            result.insert(result.end(), cells[xidx+1][yidx].begin(), cells[xidx+1][yidx].end());
            if (!onTopSide){
                result.insert(result.end(), cells[xidx+1][yidx-1].begin(), cells[xidx+1][yidx-1].end());
            }
            if (!onBottomSide){
                result.insert(result.end(), cells[xidx+1][yidx+1].begin(), cells[xidx+1][yidx+1].end());
            }
        }

        if (!onTopSide){
            result.insert(result.end(), cells[xidx][yidx-1].begin(), cells[xidx][yidx-1].end());
        }
        if (!onBottomSide){
            result.insert(result.end(), cells[xidx][yidx+1].begin(), cells[xidx][yidx+1].end());
        }

        return result;
    }

    bool hasStaticCollider(EntityID entity){
        ColliderComponent& collider = Game::get().getECS().getComponent<ColliderComponent>(entity);

        if (std::holds_alternative<RectColliderComponent>(collider)){
            return std::get<RectColliderComponent>(collider).isStatic;
        }
        else if (std::holds_alternative<CircleColliderComponent>(collider)){
            return std::get<CircleColliderComponent>(collider).isStatic;
        }

        debug::error("What type is this fucking collider ? Is this even a collider ?");
        return false;
    }

}