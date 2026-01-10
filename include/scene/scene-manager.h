#pragma once

#include <unordered_map>
#include <string_view>
#include <memory>
#include "scene/scene.h"

namespace Crankhy{

    class SceneManager{
    private:
        std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;

        std::shared_ptr<Scene> currentScene;
        std::string currentSceneName;

    public:
        SceneManager() = default;
        ~SceneManager() = default;
        void registerScene(std::string_view sceneName, std::shared_ptr<Scene> scene);
        void loadScene(std::string_view sceneName);
    };

}