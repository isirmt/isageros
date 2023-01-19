#include "SceneManager.hpp"

#include "SceneBase.hpp"

Scene::SceneBase* Scene::SceneManager::currentScene = nullptr;

void Scene::SceneManager::ChangeScene(SceneBase* _scene) {
  if (currentScene != nullptr) delete (currentScene);
  currentScene = _scene;
}