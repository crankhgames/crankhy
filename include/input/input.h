#pragma once
#include "SDL2/SDL.h"
#include <bitset>
#include "math/vector.h"

namespace Crankhy{

    namespace Input{


        bool getKeyState(SDL_Scancode scancode);
        bool getMouseState(Uint8 button);
        Vector getScreenMousePosition();

        extern const Uint8* keys;
    }
}