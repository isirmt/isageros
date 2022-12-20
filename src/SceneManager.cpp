#include "inc/SceneManager.hpp"
#include "inc/SceneBase.hpp"

Scene::SceneBase* Scene::SceneManager::currentScene = nullptr;

void Scene::SceneManager::ChangeScene(SceneBase* _scene){
    currentScene = _scene;
}