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
            Game::get().getECSManager().addType2Bitset<VelocityComponent>(systemBitset);
            Game::get().getECSManager().addType2Bitset<MoveOnInputComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                VelocityComponent &eVelocity = Game::get().getECSManager().getComponent<VelocityComponent>(entity);
                MoveOnInputComponent &eMoveOnInput = Game::get().getECSManager().getComponent<MoveOnInputComponent>(entity);

                Vector dir = Vector(0, 0);

                const float SPEED = 400.0f;

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

                eVelocity.velocity = dir.normal() * SPEED;
            }
        }
    };

}