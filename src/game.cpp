#include "game.h"
#include "ecs/ecs.h"
#include "ecs/system.h"
#include "ecs/ecs-manager.h"
#include "input/input-manager.h"

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
    case SDL_MOUSEBUTTONDOWN:
        break;
    case SDL_MOUSEBUTTONUP:
        break;
    case SDL_KEYDOWN:
        inputManager.setPressed(event.key.keysym.scancode);
        break;
    case SDL_KEYUP:
        inputManager.setReleased(event.key.keysym.scancode);
        break;
    case SDL_QUIT:
        gameState = GameState::EXIT;
        break;
    }
}

void Game::loop()
{
    handleEvent();
    window->clearRender();

    // Main logic
    ecsManager->tick(0.005);

    window->presentRender();
}

void Game::registerComponents()
{
    ecsManager->registerComponent<Transform>();
    ecsManager->registerComponent<TextureRenderer>();
    ecsManager->registerComponent<Velocity>();
    ecsManager->registerComponent<MoveOnInput>();
}

void Game::registerSystems()
{
    ecsManager->registerSystem<MoveOnInputSystem>();
    ecsManager->registerSystem<VelocitySystem>();
    ecsManager->registerSystem<RenderSystem>();
}

void Game::initializeEntities()
{
    EntityID player = ecsManager->createEntity();

    Transform pTransform;
    pTransform.position.set(400, 300);
    pTransform.scale.set(50, 50);
    ecsManager->addComponent<Transform>(player, pTransform);

    TextureRenderer pTexRenderer;
    pTexRenderer.texture = loadTexture("assets/sprites/player-sprite.png");
    ecsManager->addComponent<TextureRenderer>(player, pTexRenderer);

    Velocity pVelocity;
    pVelocity.velocity.set(0, 0);
    ecsManager->addComponent<Velocity>(player, pVelocity);

    MoveOnInput pMoveOnInput;
    pMoveOnInput.down = SDL_SCANCODE_S;
    pMoveOnInput.up = SDL_SCANCODE_W;
    pMoveOnInput.left = SDL_SCANCODE_A;
    pMoveOnInput.right = SDL_SCANCODE_D;
    ecsManager->addComponent<MoveOnInput>(player, pMoveOnInput);

}