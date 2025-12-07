#pragma once
#include "SDL2/SDL.h"
#include <bitset>

struct InputManager
{
    std::bitset<SDL_NUM_SCANCODES> keys;

    void setPressed(SDL_Scancode scancode);
    void setReleased(SDL_Scancode scancode);
    bool getKeyState(SDL_Scancode scancode);
};

extern InputManager inputManager;
