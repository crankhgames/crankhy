#include "ecs/system.h"
#include "components.h"
#include "game.h"

// Game scripts / managers
#include "graphics/texture-manager.h"

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

    void tick(int deltaTime) override
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