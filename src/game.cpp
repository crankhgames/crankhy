#include "game.h"
#include "ecs/component-manager.h"
#include "ecs/ecs.h"
#include <iostream>

Game::Game()
{
    window = nullptr;
    renderer = nullptr;

    if (Instance != nullptr)
    {
        Instance = this;
    }

    entityManager = new EntityManager();
    componentManager = new ComponentManager();
    systemManager = new SystemManager();
}

Game::~Game()
{
    delete entityManager;
    delete componentManager;
    delete systemManager;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::run()
{
    init("Error Demo", 800, 600, false);

    while (gameState != GameState::EXIT)
    {
        loop();
    }
}

void Game::init(const char *title, int width, int height, bool isFullscreen)
{

    SDL_Init(SDL_INIT_EVERYTHING);

    int fullscreenFlags = SDL_WINDOW_SHOWN;
    if (isFullscreen)
    {
        fullscreenFlags = SDL_WINDOW_FULLSCREEN;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, fullscreenFlags);
    if (!window)
    {
        std::cout << "Window not initialized..." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cout << "Renderer not initialized..." << std::endl;
        return;
    }

    gameState = GameState::PLAY;
}

void Game::handleEvent()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        gameState = GameState::EXIT;
    }
}

void Game::loop()
{
    handleEvent();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}