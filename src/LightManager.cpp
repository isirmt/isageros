#include "LightManager.hpp"

std::map<int, Scene::Light> Scene::LightManager::lights = {};
bool Scene::LightManager::beLighting = true;