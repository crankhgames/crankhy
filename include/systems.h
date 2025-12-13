#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

// Game scripts / managers
#include "math/vector.h"
#include "graphics/texture-manager.h"
#include "input/input-manager.h"

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
            Game::get().getECSManager().addType2Bitset<TextureRendererComponent>(systemBitset);
            Game::get().getECSManager().addType2Bitset<TransformComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {

                TransformComponent &transform = Game::get().getECSManager().getComponent<TransformComponent>(entity);
                TextureRendererComponent &renderer = Game::get().getECSManager().getComponent<TextureRendererComponent>(entity);

                SDL_Rect dest;
                dest.h = (int)transform.scale.y;
                dest.w = (int)transform.scale.x;
                dest.x = (int)transform.position.x;
                dest.y = (int)transform.position.y;

                draw(renderer.sprite, dest);
            }
        }
    };

    class VelocitySystem : public System
    {
    public:
        VelocitySystem()
        {
            Game::get().getECSManager().addType2Bitset<VelocityComponent>(systemBitset);
            Game::get().getECSManager().addType2Bitset<TransformComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                TransformComponent &eTransform = Game::get().getECSManager().getComponent<TransformComponent>(entity);
                VelocityComponent &eVelocity = Game::get().getECSManager().getComponent<VelocityComponent>(entity);

                eTransform.position += eVelocity.velocity;
            }
        }
    };

    class MoveOnInputSystem : public System
    {
    public:
        MoveOnInputSystem()
        {
            Game::get().getECSManager().addType2Bitset<VelocityComponent>(systemBitset);
            Game::get().getECSManager().addType2Bitset<MoveOnInputComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                VelocityComponent &eVelocity = Game::get().getECSManager().getComponent<VelocityComponent>(entity);
                MoveOnInputComponent &eMoveOnInput = Game::get().getECSManager().getComponent<MoveOnInputComponent>(entity);

                Vector dir;

                const float SPEED = 0.2;

                if (inputManager.getKeyState(eMoveOnInput.left))
                {
                    dir.x = -1;
                }
                else if (inputManager.getKeyState(eMoveOnInput.right))
                {
                    dir.x = 1;
                }
                else
                {
                    dir.x = 0;
                }

                if (inputManager.getKeyState(eMoveOnInput.up))
                {
                    dir.y = -1;
                }
                else if (inputManager.getKeyState(eMoveOnInput.down))
                {
                    dir.y = 1;
                }
                else
                {
                    dir.y = 0;
                }

                eVelocity.velocity = dir.normal() * SPEED;
            }
        }
    };
}