#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

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

                    SDL_Rect dest;
                    dest.h = (int)transform.scale.y;
                    dest.w = (int)transform.scale.x;
                    dest.x = (int)transform.position.x;
                    dest.y = (int)transform.position.y;

                    //debug::log("Scale: ", transform.scale.x, "; ", transform.scale.y);
                    //debug::log("Rendering sprite of ", entity);
                    draw(renderer.sprite, dest);
                }
            }
        };
}