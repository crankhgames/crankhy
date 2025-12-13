#include "graphics/sprite.h"
#include "graphics/texture-manager.h"

namespace Crankhy {

    Sprite::Sprite(const char* filename){
        texture = loadTexture(filename);
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);

        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = width;
        srcRect.h = height;
    }

    Spritesheet::Spritesheet(const char* filename, int numberOfSpritesX, int numberOfSpritesY){
        texture = loadTexture(filename);
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);

        srcRect.x = 0;
        srcRect.y = 0;
        currentSpriteIndex = 0;

        srcRect.w = width / numberOfSpritesX;
        srcRect.h = height / numberOfSpritesX;
    }
    
    void Spritesheet::changeSprite(int spriteIndex){
        if (currentSpriteIndex == spriteIndex){
            return;
        }

        srcRect.x = (spriteIndex % numberOfSpritesX) * srcRect.w;
        srcRect.y = (spriteIndex / numberOfSpritesY) * srcRect.h;
    }
}