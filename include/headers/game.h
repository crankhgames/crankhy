#pragma once
#include "SDL2/SDL.h"
#include "ecs/ecs-manager.h"
#include "window.h"
#include "debug.h"

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

    void init();
    void loop();
    void handleEvent();

    void registerComponents();
    void registerSystems();
    void initializeEntities();

    static Game *Instance;

    GameState gameState;

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
