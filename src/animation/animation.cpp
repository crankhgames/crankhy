#include "animation/animation.h"

namespace Crankhy{
    void AnimationManager::changeState(const std::string& stateName){
        currentState = &states[stateName];
        currentState->frameCurrent = currentState->frameStart;
        currentState->counter = currentState->delayBtwFrames;
    }



    //void AnimationManager::addState(std::string_view stateName, const AnimationState& state){
        //states[std::string(stateName)] = state;
    //}

    //void AnimationManager::addState(std::string_view stateName, AnimationState&& state){
        //states[std::string(stateName)] = std::move(state);
    //}

    AnimationState& AnimationManager::addState(std::string_view stateName, int start, int end, float delay){
        std::string name = std::string(stateName);
        states[name] = AnimationState(start, end, delay, this);
        if (currentState == nullptr){
            changeState(name);
        }
        return states[name];
    }
};
