#include "input/input.h"
#include "debug.h"

namespace Crankhy {

    namespace Input{

        bool getKeyState(SDL_Scancode scancode) {
            return keys[scancode];
        }

        bool getMouseState(Uint8 button){
            return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
        }

        Vector getScreenMousePosition(){
            int x,y;
            SDL_GetMouseState(&x, &y);
            return Vector(x, y);
        }

        const Uint8 * keys = SDL_GetKeyboardState(NULL);
    }

}