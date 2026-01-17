#include "scene/scene.h"
#include "game.h"



namespace Crankhy{

    void spawnBlock(){

        EntityID block = Game::get().getECS().createEntity();

        float randomRadius = rand() / (float)RAND_MAX * 45 + 15;
        float randomX = rand() / (float)RAND_MAX * 700 + 50;
        float randomY = rand() / (float)RAND_MAX * 500 + 50;

        Game::get().getECS().addComponent(block, 
            TransformComponent{
                .position = Vector(randomX, randomY),
                .scale = Vector(randomRadius*2, randomRadius*2)
            }
        );

        Game::get().getECS().addComponent(block, 
            TextureRendererComponent{
                .sprite = new Spritesheet("assets/sprites/player-sprite.png", 1, 1)
            }
        );

        Game::get().getECS().addComponent(block, 
            VelocityComponent{
                .velocity = Vector()
            }
        );

        Game::get().getECS().addComponent<ColliderComponent>(block, 
            RectColliderComponent{
                .bounds = Vector(randomRadius*2, randomRadius*2),
                .isStatic = true
            }
        );
    }

    void MainScene::initializeEntities() {
        for (int i = 0; i < 2; i++){
            spawnBlock();
        }

        EntityID player = Game::get().getECS().createEntity();

        Game::get().getECS().addComponent(player, 
            TransformComponent{
                .position = Vector(400, 300),
                .scale = Vector(100, 100)
            }
        );

        Game::get().getECS().addComponent(player, 
            TextureRendererComponent{
                .sprite = new Spritesheet("assets/sprites/hollow-knight-sheet.png", 12, 10)
            }
        );

        Game::get().getECS().addComponent(player, 
            AnimationRendererComponent{
                .startFrame=78,
                .endFrame=83,
                .nextFrameCounter=.1f,
                .currentFrame=78,
            }
        );


        Game::get().getECS().addComponent(player, 
            VelocityComponent{
                .velocity = Vector()
            }
        );

        Game::get().getECS().addComponent(player, 
            MoveOnInputComponent{
                .up = SDL_SCANCODE_W,
                .down = SDL_SCANCODE_S,
                .left = SDL_SCANCODE_A,
                .right = SDL_SCANCODE_D
            }
        );

        RectColliderComponent pCollider;
        Game::get().getECS().addComponent<ColliderComponent>(player, 
            RectColliderComponent{
                pCollider.bounds = Vector(100, 100),
                pCollider.isStatic = false
            }

        );


    }

    void SecondaryScene::initializeEntities(){
        EntityID player = Game::get().getECS().createEntity();

        Game::get().getECS().addComponent(player, 
            TransformComponent{
                .position = Vector(400, 300),
                .scale = Vector(100, 100)
            }
        );


        Game::get().getECS().addComponent(player, 
            TextureRendererComponent{
                .sprite = new Spritesheet("assets/sprites/logo.png", 1, 1)
            }
        );

        Game::get().getECS().addComponent(player, 
            VelocityComponent{
                .velocity = Vector()
            }
        );

        Game::get().getECS().addComponent(player, 
            MoveOnInputComponent{
                .up = SDL_SCANCODE_W,
                .down = SDL_SCANCODE_S,
                .left = SDL_SCANCODE_A,
                .right = SDL_SCANCODE_D
            }
        );
       
    }
}