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
        

    class FaceInVelocitySystem : public System
    {
        public:
            FaceInVelocitySystem()
            {
                Game::get().getECS().addType2Bitset<VelocityComponent>(systemBitset);
                Game::get().getECS().addType2Bitset<TextureRendererComponent>(systemBitset);
            }

            void tick(float deltaTime) override
            {
                for (EntityID entity : entities)
                {
                    VelocityComponent& vel = Game::get().getECS().getComponent<VelocityComponent>(entity);
                    TextureRendererComponent& tex = Game::get().getECS().getComponent<TextureRendererComponent>(entity);

                    tex.flipX = vel.velocity.x < 0.f;
                }
            }
        };
}