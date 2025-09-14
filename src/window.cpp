#include "window.h"
#include "debug.h"

void Window::init()
{
    int fullscreenFlags = SDL_WINDOW_SHOWN;
    if (isFullscreen)
    {
        fullscreenFlags = SDL_WINDOW_FULLSCREEN;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, fullscreenFlags);
    if (!window)
    {
        debug::error("Window not initialized...");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        debug::error("Renderer not initialized...");
        return;
    }
}

void Window::clearRender()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void Window::presentRender()
{
    SDL_RenderPresent(renderer);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}