#include "game.h"
#include "ecs/ecs.h"
#include "ecs/system.h"
#include "ecs/ecs-manager.h"
#include "components.h"
#include "systems.h"

#include "debug.h"
#include <iostream>
#include <memory>

Game *Game::Instance = nullptr;
Game::Game()
{
    if (Instance == nullptr)
    {
        Instance = this;
    }
    window = std::make_unique<Window>();
    ecsManager = std::make_unique<ECSManager>();
}

void Game::run()
{
    init();

    while (gameState != GameState::EXIT)
    {
        loop();
    }
}

void Game::init()
{

    SDL_Init(SDL_INIT_EVERYTHING);
    srand(std::time(NULL));

    window->init();
    debug::log("Window initialized !");
    registerComponents();
    debug::log("Components registered !");
    registerSystems();
    debug::log("Systems registered !");
    initializeEntities();
    debug::log("Entities intialized !");

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
    window->clearRender();

    // Main logic
    ecsManager->tick(0.1);

    window->presentRender();
}

void Game::registerComponents()
{
    ecsManager->registerComponent<Transform>();
    ecsManager->registerComponent<TextureRenderer>();
    ecsManager->registerComponent<Velocity>();
}

void Game::registerSystems()
{
    ecsManager->registerSystem(std::make_shared<RenderSystem>());
}

void Game::initializeEntities()
{

    for (int i = 0; i < 50; i++)
    {
        EntityID player = ecsManager->createEntity();

        // Creates Transform component
        Transform playerTransform;
        int x = (float)rand() / RAND_MAX * 800;
        int y = (float)rand() / RAND_MAX * 600;
        playerTransform.position.set(x, y);
        playerTransform.scale.set(50, 50);
        ecsManager->addComponent<Transform>(player, playerTransform);

        // Creates TextureRenderer component
        TextureRenderer playerRenderer;
        playerRenderer.texture = loadTexture("assets/sprites/player-sprite.png");
        ecsManager->addComponent<TextureRenderer>(player, playerRenderer);
    }
}