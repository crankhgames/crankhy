#include "scene/scene-manager.h"
#include "game.h"
#include "debug.h"

namespace Crankhy{

void SceneManager::loadScene(std::string_view sceneName){
    currentSceneName = sceneName;
    std::string name = (std::string)sceneName;
    currentScene = scenes[name];
    Game::get().getECSManager().clearEntities();
    currentScene->initializeEntities();
}

void SceneManager::registerScene(std::string_view sceneName, std::shared_ptr<Scene> scene){
    scenes.insert(std::pair<std::string, std::shared_ptr<Scene>>(sceneName, scene) );
}

}