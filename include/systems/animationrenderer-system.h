#include "ecs/system.h"
#include "scene/components.h"
#include "game.h"

// Game scripts / managers
#include "math/vector.h"
#include "graphics/texture-manager.h"

// SDL header files
#include "SDL2/SDL.h"

#include "debug.h"

namespace Crankhy{

    class AnimationRendererSystem : public System
    {
    public:
        AnimationRendererSystem()
        {
            Game::get().getECS().addType2Bitset<AnimationRendererComponent>(systemBitset);
            Game::get().getECS().addType2Bitset<TextureRendererComponent>(systemBitset);
        }

        void tick(float deltaTime) override
        {
            for (EntityID entity : entities)
            {
                AnimationRendererComponent &eAnimationRenderer = Game::get().getECS().getComponent<AnimationRendererComponent>(entity);
                TextureRendererComponent &eTextureRenderer = Game::get().getECS().getComponent<TextureRendererComponent>(entity);

                eAnimationRenderer.counter += deltaTime;
                debug::log(eAnimationRenderer.currentFrame);
                if (eAnimationRenderer.counter >= eAnimationRenderer.nextFrameCounter){
                    eAnimationRenderer.counter = 0;
                    eAnimationRenderer.currentFrame++;

                    if (eAnimationRenderer.currentFrame > eAnimationRenderer.endFrame){
                        eAnimationRenderer.currentFrame = eAnimationRenderer.startFrame;
                    }

                    eTextureRenderer.sprite->changeSprite(eAnimationRenderer.currentFrame);
                }
            }
        }
    };
}