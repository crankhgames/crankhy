#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include "ecs/ecs.h"

#include <functional>

namespace Crankhy{

    class AnimationManager;

    struct AnimationState{
    
        int frameStart, frameEnd;
        float delayBtwFrames;
        int frameCurrent;
        AnimationManager* manager;
        float counter = 0.f;
        
        std::function<void(AnimationManager*, EntityID)> transition;


        AnimationState() = default;
        ~AnimationState() = default;
        AnimationState(int start, int end, float delay, AnimationManager* manager) : frameStart(start), frameEnd(end), frameCurrent(start), delayBtwFrames(delay), manager(manager){};
    };


    class AnimationManager{

    public:
        //void addState(std::string_view stateName, const AnimationState& state);
        //void addState(std::string_view stateName, AnimationState&& state);
        
        /**
         * @brief Add State to manager
         */
        AnimationState& addState(std::string_view stateName, int start, int end, float delay);

        /**
         * @brief Change current animation state playing
         */
        void changeState(const std::string& stateName);

        AnimationState* getCurrentState() {return currentState;}

        AnimationManager() = default;
        ~AnimationManager() = default;

    private:
        AnimationState* currentState;
        std::unordered_map<std::string, AnimationState> states;

    };

}