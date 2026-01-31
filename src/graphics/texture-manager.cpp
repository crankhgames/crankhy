#include "graphics/texture-manager.h"
#include "SDL2/SDL_image.h"
#include "debug.h"
#include "game.h"
#include <unordered_map>

namespace Crankhy{

    std::unordered_map<const char *, SDL_Texture *> loadedTextures;


    SDL_Texture *loadTexture(const char *filename)
    {
        if (loadedTextures.find(filename) != loadedTextures.end())
        {
            return loadedTextures[filename];
        }

        SDL_Surface *tempSurface = IMG_Load(filename);
        if (!tempSurface)
        {
            debug::error("Failed to load image: ", filename);
            return nullptr;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::get().getWindow().renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        if (!texture)
        {
            debug::error("Failed to create texture from surface: ", filename);
            return nullptr;
        }

        loadedTextures[filename] = texture;
        return texture;
    }

    void draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest, bool flipX, bool flipY)
    {
        if (SDL_RenderCopyEx(Game::get().getWindow().renderer, texture, &src, &dest, 0, NULL, (SDL_RendererFlip)((flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | (flipY ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE))) != 0)
        {
            debug::error("Failed to render texture: ", SDL_GetError());
        }
    }

    void draw(Sprite* sprite, SDL_Rect dest, bool flipX, bool flipY){
        draw(sprite->getTexture(), sprite->getSrcRect(), dest, flipX, flipY);
    }
}