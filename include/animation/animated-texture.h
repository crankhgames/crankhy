#pragma once

#include "SDL2/SDL.h"
#include "graphics/spritesheet/spritesheet.h"

#include <memory>

namespace Crankhy {

    struct AnimatedTexture{
        
        std::shared_ptr<SpriteSheet> spriteSheet;
        int totalFrames;
        int currentSpriteIdx;
        void nextFrame();
    };
}