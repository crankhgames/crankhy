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

                //debug::log("Current frame of animation for entity ", entity, " is ", eAnimationRenderer.currentFrame);
                AnimationState* state = eAnimationRenderer.animation->getCurrentState();
                state->counter += deltaTime;

                state->transition(state->manager, entity);

                if (state->counter >= state->delayBtwFrames){
                    state->counter = 0;
                    state->frameCurrent++;

                    if (state->frameCurrent > state->frameEnd){
                        state->frameCurrent = state->frameStart;
                    }

                    eTextureRenderer.sprite->changeSprite(state->frameCurrent);
                }
            }
        }
    };
}