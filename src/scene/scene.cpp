#include "scene/scene.h"
#include "game.h"



namespace Crankhy{

    void spawnBlock(float x, float y){

        EntityID block = Game::get().getECS().createEntity();

        float size = 1.0f;

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

        Game::get().getECS().getComponent<TextureRendererComponent>(block).sprite->changeSprite(4);

        Game::get().getECS().addComponent<ColliderComponent>(block, 
            ColliderComponent {
                .type=ColliderType::Rectangle,
                .layer=CollisionLayer::LAYER_BLOCK,
                .isStatic = true,
                .shapeInfo=RectCollisionInfo{
                    .bounds=Vector(size*2, size*2)
                },

            }
        );
    }

    void MainScene::initializeEntities() {

        EntityID& cam = Game::get().getCamera();
        cam = Game::get().getECS().createEntity();

        //EntityID ball = Game::get().getECS().createEntity();

        //Game::get().getECS().addComponent(ball, 
            //TransformComponent{
                //.position = Vector(5, 5),
                //.scale= Vector(0, 0),
            //}
        //);
        //Game::get().getECS().addComponent(ball, 
            //ColliderComponent {
                //.type=ColliderType::Circle,
                //.layer=CollisionLayer::LAYER_NONE,
                //.isStatic = false,
                //.hasPhysicalPresence = false,
                //.shapeInfo=CircleCollisionInfo{
                    //.radius=10
                //},

            //}
        //);

        for (int i = 0; i < 4; i++){
            spawnBlock(i*2, 0);
            spawnBlock(i*2, 5*2);
        }

        for (int i = 6; i < 10; i++){
            spawnBlock(i*2, 0);
            spawnBlock(i*2, 5*2);
        }

        for (int i = 0; i < 6; i++){
            spawnBlock(-1*2, i*2);
            spawnBlock(10*2, i*2);
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

        Game::get().getECS().addComponent<ColliderComponent>(player, 
            ColliderComponent {
                .type=ColliderType::Rectangle,
                .layer=CollisionLayer::LAYER_PLAYER,
                .isStatic = false,
                .offset = Vector(.2f, .05f),
                .shapeInfo=RectCollisionInfo{
                    .bounds=Vector(.5f, .9f)
                },

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

        Game::get().getECS().addComponent(player, 
            ShooterComponent{
                .bulletSpeed=3.0f,
                .delayBtwShots=0.4f
            }
        );


        EntityID camEntity = Game::get().getCamera();

        Game::get().getECS().addComponent(camEntity, 
            TransformComponent{
                .position=Vector(0, 0)
            }
        );

        float pixelsToUnitCam = 100;
        Game::get().getECS().addComponent(camEntity, 
            CameraComponent{
                Vector(pixelsToUnitCam, pixelsToUnitCam)
            }
        );

        Game::get().getECS().addComponent(camEntity, 
            FollowComponent{
                .followedTransform = &Game::get().getECS().getComponent<TransformComponent>(player),
                .offset = Vector(-Game::get().getWindow().width / (2 * pixelsToUnitCam), -Game::get().getWindow().height / (2 * pixelsToUnitCam)) // Centering player on center of screen
            }
        );

    }

}