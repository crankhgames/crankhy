#pragma once
#include "SDL2/SDL.h"
#include "ecs/entity-manager.h"
#include "ecs/component-manager.h"
#include "ecs/system-manager.h"

enum class GameState
{
    PLAY,
    EXIT
};

class Game
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;

    EntityManager *entityManager;
    ComponentManager *componentManager;
    SystemManager *systemManager;

    void init(const char *title, int width, int height, bool isfullscreen);
    void loop();
    void handleEvent();

    static Game *Instance;

    GameState gameState;

public:
    Game();
    ~Game();
    void run();

    static Game *get() { return Instance; }

    SDL_Renderer *getRenderer() { return renderer; }
    SDL_Window *getWindow() { return window; }
    EntityManager *getEntityManager() { return entityManager; }
    ComponentManager *getComponentManager() { return componentManager; }
    SystemManager *getSystemManager() { return systemManager; }
};