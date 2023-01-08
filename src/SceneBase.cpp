#include "SceneBase.hpp"

void Scene::SceneBase::SetOrthoCameraWindow() {
  Camera::SetAsOrtho(PosVec(0, 0, -.1f),
                     PosVec(ApplicationPreference::windowSize.x,
                            ApplicationPreference::windowSize.y, .1f));
}

void Scene::SceneBase::Set3DDrawMode() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
}
void Scene::SceneBase::Set2DDrawMode() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
}
