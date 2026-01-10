#include "input/input.h"
#include "debug.h"

namespace Crankhy {

    namespace Input{

        void setPressed(SDL_Scancode scancode)
        {
            keys[scancode] = true;
        }

        void setReleased(SDL_Scancode scancode)
        {
            keys[scancode] = false;
        }

        bool getKeyState(SDL_Scancode scancode)
        {
            return keys[scancode];
        }

        std::bitset<SDL_NUM_SCANCODES> keys;
    }

}