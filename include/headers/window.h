#pragma once
#include "SDL2/SDL.h"

struct Window
{
    SDL_Renderer *renderer;
    SDL_Window *window;

    // Title name of the window (sits on top of the window)
    const char *title = "Err0r Demo";

    // Dimensions of the window
    const int width = 800;
    const int height = 600;

    const bool isFullscreen = false;

    // Initialize SDL_Renderer and SDL_Window
    void init();
    // Clear the render, draws the background
    void clearRender();
    // Present the render to the window
    void presentRender();

    ~Window();
};