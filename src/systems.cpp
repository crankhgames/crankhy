#include "ecs/system.h"
#include "components.h"
#include "game.h"
#include "SDL.h"
#include "managers/texture-manager.h"
#include "SDL_image.h"

class RenderSystem : public System
{
public:
    void tick(int deltaTime) override
    {
        for (EntityID entity : entities)
        {

            Transform &transform = Game::get()->getComponentManager()->getComponent<Transform>(entity);
            Renderer &renderer = Game::get()->getComponentManager()->getComponent<Renderer>(entity);

            int width, height;
            SDL_QueryTexture(renderer.texture, NULL, NULL, &width, &height);

            SDL_Rect src{
                width, height, 0, 0};

            SDL_Rect dest{
                transform.scaleX, transform.scaleY, transform.x, transform.y};

            draw(renderer.texture, src, dest);
        }
    }
};