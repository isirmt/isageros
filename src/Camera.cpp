#include "Camera.hpp"

bool Scene::Camera::isActive = true;
bool Scene::Camera::isPerspective = true;

float Scene::Camera::fov = 0;
float Scene::Camera::wph = 0;
float Scene::Camera::far = 0;
float Scene::Camera::near= 0;
PosVec Scene::Camera::r = PosVec();
PosVec Scene::Camera::lookAt = PosVec();
PosVec Scene::Camera::vec = PosVec();
PosVec Scene::Camera::from = PosVec();
PosVec Scene::Camera::to = PosVec();
