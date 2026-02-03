#pragma once

#include "ecs/ecs.h"
#include "scene/components.h"

namespace Crankhy{

    class Game;

    class Scene{
    public:
        ~Scene() = default;
        virtual void initializeEntities(){};
    };


    class MainScene : public Scene{
    public:
        void initializeEntities() override;
    };
}