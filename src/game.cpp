#include "game.h"
#include "ecs/ecs.h"
#include "ecs/system.h"
#include "ecs/ecs-manager.h"
#include "input/input.h"

#include "scene/components.h"
#include "systems/systems.h"


#include "debug.h"
#include <iostream>
#include <memory>

namespace Crankhy{

    Game *Game::Instance = nullptr;
    Game::Game()
    {
        if (Instance == nullptr)
        {
            Instance = this;
        }
        window = std::make_unique<Window>();
        ecs = std::make_unique<ECSManager>();
        sceneManager = std::make_unique<SceneManager>();

        sceneManager->registerScene("Main", std::make_shared<MainScene>());

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
            break;
        }
    
        SDL_PumpEvents();
    }

    void Game::loop()
    {
        Uint64 frameStart = SDL_GetTicks64();

        handleEvent();

        window->clearRender();

        // Main logic
        ecs->tick(deltatime);


        Uint64 deltaMilliseconds = SDL_GetTicks64() - frameStart;
        deltatime = deltaMilliseconds / 1000.0f;
        if (deltatime < 1.0f / FPS){
            SDL_Delay(1000 / FPS - deltaMilliseconds);
            deltatime = 1.0f / FPS;
        }
        debug::log("Framerate: ", 1/deltatime, " FPS");

        TransformComponent& camTransform = ecs->getComponent<TransformComponent>(*cameraEntity);
        debug::log("Camera pos: ", camTransform.position.x, "; ", camTransform.position.y);


        window->presentRender();
    }

    void Game::registerComponents()
    {
        ecs->registerComponent<TransformComponent>();
        ecs->registerComponent<TextureRendererComponent>();
        ecs->registerComponent<VelocityComponent>();
        ecs->registerComponent<MoveOnInputComponent>();
        ecs->registerComponent<ColliderComponent>();
        ecs->registerComponent<AnimationRendererComponent>();
        ecs->registerComponent<CameraComponent>();
        ecs->registerComponent<FollowComponent>();
        ecs->registerComponent<ShooterComponent>();
        ecs->registerComponent<LifetimeComponent>();
    }

    void Game::registerSystems()
    {
        ecs->registerSystem<MoveOnInputSystem>();
        ecs->registerSystem<VelocitySystem>();
        ecs->registerSystem<FollowSystem>();
        ecs->registerSystem<AnimationRendererSystem>();
        ecs->registerSystem<BulletSystem>();
        ecs->registerSystem<LifetimeSystem>();
        ecs->registerSystem<RenderSystem>();
        ecs->registerSystem<CollisionSystem>();
    }

    void Game::initializeEntities()
    {
        sceneManager->loadScene("Main");
    }
}
