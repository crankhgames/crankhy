#include "scene/scene.h"
#include "game.h"



namespace Crankhy{

    void spawnBlock(float x, float y){

        EntityID block = Game::get().getECS().createEntity();

        float size = 0.5f;

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

        Game::get().getECS().getComponent<TextureRendererComponent>(block).sprite->changeSprite(7);

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

    void spawnEnemy(float x, float y, EntityID player){

        EntityID fuckingworm = Game::get().getECS().createEntity();

        Game::get().getECS().addComponent(fuckingworm, 
            TransformComponent{
                .position = Vector(x, y),
                .scale = Vector(2, 2)
            }
        );

        
        Game::get().getECS().addComponent(fuckingworm, 
            TextureRendererComponent{
                .sprite = new Spritesheet("assets/sprites/hollow-knight-sheet.png", 12, 10)
            }
        );


        AnimationManager* fuckingWormAnimationManager = new AnimationManager();
        AnimationState& walkState = fuckingWormAnimationManager->addState("Walk", 17, 23, .1f); 

        walkState.transition = [](AnimationManager* animManager, EntityID entity) {
        };

        Game::get().getECS().addComponent(fuckingworm, 
            AnimationRendererComponent{
                .animation=fuckingWormAnimationManager
            }
        );
        //Game::get().getECS().addComponent(fuckingworm, 
            //AnimationRendererComponent{
                //.startFrame=17,
                //.endFrame=23,
                //.nextFrameCounter=.1f,
                //.currentFrame=17,
            //}
        //);

        Game::get().getECS().addComponent(fuckingworm,
            ColliderComponent{
                .type=ColliderType::Circle,
                .layer=CollisionLayer::LAYER_ENEMY,
                .isStatic=false,
                .hasPhysicalPresence=true,
                .offset={.7f, 1.f},
                .shapeInfo=CircleCollisionInfo{
                    .radius=.5f
                },
            }
        );

        Game::get().getECS().addComponent(fuckingworm, 
            VelocityComponent{
            }
        );

        Game::get().getECS().addComponent(fuckingworm, 
            FollowBehaviourComponent{
                .followedTransform= &Game::get().getECS().getComponent<TransformComponent>(player),
                .speed = 1.5f
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
            spawnBlock(i, 0);
            spawnBlock(i, 5);
        }

        for (int i = 6; i < 10; i++){
            spawnBlock(i, 0);
            spawnBlock(i, 5);
        }

        for (int i = 0; i < 6; i++){
            spawnBlock(-1, i);
            spawnBlock(10, i);
        }


        for (int i = -3; i < 9; i++){
            spawnBlock(-4, i);
            spawnBlock(13, i);
        }
        for (int i = -3; i < 13; i++){
            spawnBlock(i, -3);
            spawnBlock(i, 8);
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

        AnimationManager* playerAnimationManager = new AnimationManager();
        AnimationState& walkState = playerAnimationManager->addState("Walk", 0, 8, .1f); 
        AnimationState& idleState =  playerAnimationManager->addState("Idle", 66, 71, .4f); 

        walkState.transition = [](AnimationManager* animManager, EntityID entity) {
            VelocityComponent& velocity = Game::get().getECS().getComponent<VelocityComponent>(entity);
            if (velocity.velocity.x == 0 && velocity.velocity.y == 0){
                animManager->changeState("Idle");
            }
        };

        idleState.transition = [](AnimationManager* animManager, EntityID entity) {
            VelocityComponent& velocity = Game::get().getECS().getComponent<VelocityComponent>(entity);
            if (velocity.velocity.x != 0 || velocity.velocity.y != 0){
                animManager->changeState("Walk");
            }
        };

        Game::get().getECS().addComponent(player, 
            AnimationRendererComponent{
                .animation=playerAnimationManager
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
                .bulletSpeed=5.0f,
                .delayBtwShots=0.4f
            }
        );

        // Following ent

        //for (int i{1}; i < 7; i++){
            //spawnEnemy(i + 2, -i, player);
            //spawnEnemy(-i + 2, i, player);
            //spawnEnemy(i + 2, i, player);
            //spawnEnemy(-i + 2, -i, player);
        //}

        for (int i = 0; i <2; i++) {
            EntityID spawner = Game::get().getECS().createEntity();
            
            Game::get().getECS().addComponent(spawner,
                TransformComponent{
                    .position = Vector(5 + 3*i, 4 + 1*i),
                    .scale= Vector(0, 0)
                }
            );

            Game::get().getECS().addComponent(spawner,
                SpawnerComponent{
                    .delayBtwSpawns=.3f,
                    .spawnFunc = spawnEnemy,
                    .player = player,
                    .counter=1.f,
                }
            );
        }


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