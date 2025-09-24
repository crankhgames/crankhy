#include "ecs/system.h"
#include "components.h"
#include "game.h"

// Game scripts / managers
#include "math/vector.h"
#include "graphics/texture-manager.h"
#include "input/input-manager.h"

// SDL header files
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "debug.h"

class RenderSystem : public System
{

public:
    RenderSystem()
    {
        Game::get().getECSManager().addType2Bitset<TextureRenderer>(systemBitset);
        Game::get().getECSManager().addType2Bitset<Transform>(systemBitset);
    }

    void tick(float deltaTime) override
    {
        for (EntityID entity : entities)
        {

            Transform &transform = Game::get().getECSManager().getComponent<Transform>(entity);
            TextureRenderer &renderer = Game::get().getECSManager().getComponent<TextureRenderer>(entity);

            int width, height;
            SDL_QueryTexture(renderer.texture, NULL, NULL, &width, &height);

            SDL_Rect src;
            src.h = height;
            src.w = width;
            src.x = 0;
            src.y = 0;

            SDL_Rect dest;
            dest.h = (int)transform.scale.y;
            dest.w = (int)transform.scale.x;
            dest.x = (int)transform.position.x;
            dest.y = (int)transform.position.y;
            draw(renderer.texture, src, dest);
        }
    }
};

class VelocitySystem : public System
{
public:
    VelocitySystem()
    {
        Game::get().getECSManager().addType2Bitset<Velocity>(systemBitset);
        Game::get().getECSManager().addType2Bitset<Transform>(systemBitset);
    }

    void tick(float deltaTime) override
    {
        for (EntityID entity : entities)
        {
            Transform &eTransform = Game::get().getECSManager().getComponent<Transform>(entity);
            Velocity &eVelocity = Game::get().getECSManager().getComponent<Velocity>(entity);

            eTransform.position += eVelocity.velocity;
        }
    }
};

class MoveOnInputSystem : public System
{
public:
    MoveOnInputSystem()
    {
        Game::get().getECSManager().addType2Bitset<Velocity>(systemBitset);
        Game::get().getECSManager().addType2Bitset<MoveOnInput>(systemBitset);
    }

    void tick(float deltaTime) override
    {
        for (EntityID entity : entities)
        {
            Velocity &eVelocity = Game::get().getECSManager().getComponent<Velocity>(entity);
            MoveOnInput &eMoveOnInput = Game::get().getECSManager().getComponent<MoveOnInput>(entity);

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