#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"
#include "graphics/camera.h"

// Game scripts / managers
#include "graphics/texture-manager.h"

// SDL header files
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "debug.h"

namespace Crankhy{
        

    class RenderSystem : public System
    {
        public:
            RenderSystem()
            {
                Game::get().getECS().addType2Bitset<TextureRendererComponent>(systemBitset);
                Game::get().getECS().addType2Bitset<TransformComponent>(systemBitset);
            }

            void tick(float deltaTime) override
            {
                for (EntityID entity : entities)
                {

                    TransformComponent &transform = Game::get().getECS().getComponent<TransformComponent>(entity);
                    TextureRendererComponent &renderer = Game::get().getECS().getComponent<TextureRendererComponent>(entity);


                    EntityID cameraEntity = Game::get().getCamera();
                    TransformComponent& camTransform = Game::get().getECS().getComponent<TransformComponent>(cameraEntity);
                    CameraComponent& camComponent = Game::get().getECS().getComponent<CameraComponent>(cameraEntity);
                    //debug::log("Camera Entity: ", cameraEntity, "; ", "Rendered entity: ", entity);

                    //debug::log("Scale: ", transform.scale.x, "; ", transform.scale.y);
                    //debug::log("Rendering sprite of ", entity);
                    SDL_Rect position = localToScreen(camTransform, camComponent, transform);

                    //if (position.x + position.w < 0 || position.x > Game::get().getWindow().width || position.y > Game::get().getWindow().height || position.x + position.h < 0)
                        //continue;
                    draw(renderer.sprite, position, renderer.flipX, renderer.flipY);
                }
            }
        };
}