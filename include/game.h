#pragma once
#include "SDL2/SDL.h"
#include "ecs/ecs-manager.h"
#include "window.h"
#include "debug.h"

#include "scene/scene.h"
#include "scene/scene-manager.h"

namespace Crankhy{

    enum class GameState
    {
        PLAY,
        EXIT
    };

    class Game
    {
    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<ECSManager> ecsManager;
        std::unique_ptr<SceneManager> sceneManager;

        GameState gameState;

        const int FPS = 60;
        float deltatime = 0;

        void init();
        void loop();
        void handleEvent();

        void registerComponents();
        void registerSystems();
        void initializeEntities();

        static Game *Instance;


    public:
        Game();
        ~Game() = default;
        void run();

        static Game &get()
        {
            return *Instance;
        }

        Window &getWindow()
        {
            return *window.get();
        }
        ECSManager &getECSManager()
        {
            return *ecsManager.get();
        }
    };
}