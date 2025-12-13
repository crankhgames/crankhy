#include "input/input-manager.h"
#include "debug/debug.h"

namespace Crankhy {

    void InputManager::setPressed(SDL_Scancode scancode)
    {
        keys[scancode] = true;
    }

    void InputManager::setReleased(SDL_Scancode scancode)
    {
        keys[scancode] = false;
    }

    bool InputManager::getKeyState(SDL_Scancode scancode)
    {
        return keys[scancode];
    }

    InputManager inputManager;
}