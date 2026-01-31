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
                    draw(renderer.sprite, localToScreen(camTransform, camComponent, transform), renderer.flipX, renderer.flipY);
                }
            }
        };
}