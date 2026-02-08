#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

#include "input/input.h"
#include "graphics/camera.h"

// SDL header files
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "debug.h"

namespace Crankhy{
        

    class BulletSystem : public System
    {
        public:
            BulletSystem()
            {
                Game::get().getECS().addType2Bitset<TransformComponent>(systemBitset);
                Game::get().getECS().addType2Bitset<ShooterComponent>(systemBitset);
            }

            void tick(float deltaTime) override
            {
                for (EntityID entity : entities)
                {
                    TransformComponent &transform = Game::get().getECS().getComponent<TransformComponent>(entity);
                    ShooterComponent &shooter = Game::get().getECS().getComponent<ShooterComponent>(entity);

                    shooter.counter += deltaTime;

                    if (shooter.counter < shooter.delayBtwShots || !Input::getMouseState(SDL_BUTTON_LEFT)){
                        continue;
                    }

                    shooter.counter = 0;


                    EntityID bullet = Game::get().getECS().createEntity();
                    
                    Game::get().getECS().addComponent(bullet,
                        TransformComponent{
                            .position = transform.position + transform.scale/2.f,
                            .scale = Vector(.6f, .6f)
                        }
                    );

                    TransformComponent& camTransform = Game::get().getECS().getComponent<TransformComponent>(Game::get().getCamera());
                    CameraComponent& cam = Game::get().getECS().getComponent<CameraComponent>(Game::get().getCamera());
                    Vector mousePosition = Input::getScreenMousePosition();
                    Vector bulletVel = screenToLocal(camTransform, cam, mousePosition) - (transform.position + transform.scale / 2);

                    Game::get().getECS().addComponent(bullet,
                        VelocityComponent{
                            .velocity = bulletVel.normal() * shooter.bulletSpeed
                        }
                    );

                    Game::get().getECS().addComponent(bullet,
                        TextureRendererComponent{
                            .sprite=new Spritesheet("assets/sprites/player-sprite.png", 1, 1)
                        }
                    );

                    Game::get().getECS().addComponent(bullet,
                        LifetimeComponent{
                            .totalLifetime=10.0f
                        }
                    );

                    Game::get().getECS().addComponent(bullet,
                        ColliderComponent{
                            .type = ColliderType::Circle,
                            .layer = CollisionLayer::LAYER_BULLET,
                            .isStatic = false,
                            .shapeInfo = CircleCollisionInfo{
                                .radius=.3f
                            }
                        }
                    );


                }
            }
        };
}