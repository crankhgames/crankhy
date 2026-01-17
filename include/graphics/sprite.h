#pragma once

#include "SDL2/SDL.h"
#include <memory>

namespace Crankhy {

    class Sprite{
        
    protected:
        SDL_Texture* texture;
        SDL_Rect srcRect;

        int width, height;

    public:
        Sprite() = default;
        Sprite(const char* filename);

        SDL_Texture* getTexture() {return texture;}
        SDL_Rect getSrcRect() {return srcRect;}
    };

    class Spritesheet : public Sprite{

    private:
        int currentSpriteIndex = 0;
        int numberOfSpritesX, numberOfSpritesY;

    public:
        Spritesheet(const char* filename, int numberOfSpritesX, int numberOfSpritesY);
        void changeSprite(int spriteIndex);
    };

}