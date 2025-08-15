#include "managers/texture-manager.h"
#include "SDL_image.h"
#include "debug.h"
#include "game.h"

SDL_Texture *loadTexture(const char *filename)
{
    SDL_Surface *tempSurface = IMG_Load(filename);
    if (!tempSurface)
    {
        debug::error("Failed to load image: ", filename);
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::get()->getRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture)
    {
        debug::error("Failed to create texture from surface: ", filename);
        return nullptr;
    }

    return texture;
}

void draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest)
{
    if (SDL_RenderCopy(Game::get()->getRenderer(), texture, &src, &dest) != 0)
    {
        debug::error("Failed to render texture: ", SDL_GetError());
    }
}