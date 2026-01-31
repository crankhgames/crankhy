#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

// Game scripts / managers
#include "math/vector.h"
#include "graphics/texture-manager.h"
#include "input/input.h"

// SDL header files
#include "SDL2/SDL.h"

#include "debug.h"

namespace Crankhy{ 


    class MoveOnInputSystem : public System
    {
    public:
        MoveOnInputSystem()
        {
            Game::get().getECS().addType2Bitset<VelocityComponent>(systemBitset);
            Game::get().getECS().addType2Bitset<MoveOnInputComponent>(systemBitset);
            Game::get().getECS().addType2Bitset<TextureRendererComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                VelocityComponent &eVelocity = Game::get().getECS().getComponent<VelocityComponent>(entity);
                MoveOnInputComponent &eMoveOnInput = Game::get().getECS().getComponent<MoveOnInputComponent>(entity);
                TextureRendererComponent &eTexRenderer = Game::get().getECS().getComponent<TextureRendererComponent>(entity);

                Vector dir = Vector(0, 0);

                const float SPEED = 2.0f;

                if (Input::getKeyState(eMoveOnInput.left))
                {
                    dir.x = -1;
                }
                else if (Input::getKeyState(eMoveOnInput.right))
                {
                    dir.x = 1;
                }
                else
                {
                    dir.x = 0;
                }

                if (Input::getKeyState(eMoveOnInput.up))
                {
                    dir.y = -1;
                }
                else if (Input::getKeyState(eMoveOnInput.down))
                {
                    dir.y = 1;
                }
                else
                {
                    dir.y = 0;
                }

                if (dir.x != 0){
                    eTexRenderer.flipX = dir.x == -1;
                }
                eVelocity.velocity = dir.normal() * SPEED;

            }
        }
    };

}