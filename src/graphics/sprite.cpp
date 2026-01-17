#include "graphics/sprite.h"
#include "graphics/texture-manager.h"

#include "debug.h"

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

        this->numberOfSpritesX = numberOfSpritesX;
        this->numberOfSpritesY = numberOfSpritesY;

        srcRect.x = 0;
        srcRect.y = 0;
        currentSpriteIndex = 0;

        srcRect.w = width / numberOfSpritesX;
        srcRect.h = height / numberOfSpritesY;
    }
    
    void Spritesheet::changeSprite(int spriteIndex){
        debug::log("Current Sprite Index: ", currentSpriteIndex);
        if (currentSpriteIndex == spriteIndex){
            return;
        }

        srcRect.x = (spriteIndex % numberOfSpritesX) * srcRect.w;
        srcRect.y = (spriteIndex / numberOfSpritesX) * srcRect.h;
        debug::log("SRC rect x: ", srcRect.x, "; SRC rect y: ", srcRect.y);
        currentSpriteIndex = spriteIndex;
    }
}