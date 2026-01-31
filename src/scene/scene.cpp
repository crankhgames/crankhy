#include "scene/scene.h"
#include "game.h"



namespace Crankhy{

    void spawnBlock(float x, float y){

        EntityID block = Game::get().getECS().createEntity();

        float size = .5f;

        Game::get().getECS().addComponent(block, 
            TransformComponent{
                .position = Vector(x, y),
                .scale = Vector(size*2, size*2)
            }
        );

        Game::get().getECS().addComponent(block, 
            TextureRendererComponent{
                .sprite = new Spritesheet("assets/sprites/SchematicSprite.png", 32, 32)
            }
        );

        Game::get().getECS().getComponent<TextureRendererComponent>(block).sprite->changeSprite(5);

        Game::get().getECS().addComponent(block, 
            VelocityComponent{
                .velocity = Vector()
            }
        );

        Game::get().getECS().addComponent<ColliderComponent>(block, 
            RectColliderComponent{
                .bounds = Vector(size*2, size*2),
                .isStatic = true
            }
        );
    }

    void MainScene::initializeEntities() {

        EntityID& cam = Game::get().getCamera();
        cam = Game::get().getECS().createEntity();

        for (int i = 0; i < 10; i++){
            spawnBlock(i, 0);
            spawnBlock(i, 5);
        }

        for (int i = 0; i < 6; i++){
            spawnBlock(-1, i);
            spawnBlock(10, i);
        }

        EntityID player = Game::get().getECS().createEntity();


        Game::get().getECS().addComponent(player, 
            TransformComponent{
                .position = Vector(4, 3),
                .scale = Vector(1, 1)
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

        Game::get().getECS().addComponent<ColliderComponent>(player, 
            RectColliderComponent{
                .bounds = Vector(1, 1),
                .isStatic = false
            }

        );

        EntityID camEntity = Game::get().getCamera();

        Game::get().getECS().addComponent(camEntity, 
            TransformComponent{
                .position=Vector(0, 0)
            }
        );

        Game::get().getECS().addComponent(camEntity, 
            CameraComponent{
                Vector(100, 100)
            }
        );

        Game::get().getECS().addComponent(camEntity, 
            FollowComponent{
                .followedTransform = &Game::get().getECS().getComponent<TransformComponent>(player),
                .offset = Vector(-3.5, -2.5)
            }
        );

    }

    void SecondaryScene::initializeEntities(){
        EntityID& cam = Game::get().getCamera();
        cam = Game::get().getECS().createEntity();

        EntityID camEntity = Game::get().getCamera();

        Game::get().getECS().addComponent(camEntity, 
            TransformComponent{
                .position=Vector(0, 0)
            }
        );

        Game::get().getECS().addComponent(camEntity, 
            CameraComponent{
                Vector(100, 100)
            }
        );
        EntityID player = Game::get().getECS().createEntity();

        Game::get().getECS().addComponent(player, 
            TransformComponent{
                .position = Vector(400, 300),
                .scale = Vector(1, 1)
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