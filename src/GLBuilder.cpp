#include "GLBuilder.hpp"

void GLSYS::GLBuilder::GLSetup() {
  glClearColor(ApplicationPreference::defaultWorldColor.r,
               ApplicationPreference::defaultWorldColor.g,
               ApplicationPreference::defaultWorldColor.b, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-ApplicationPreference::windowSize.x / 2.,
          ApplicationPreference::windowSize.x / 2.,
          -ApplicationPreference::windowSize.y / 2.,
          ApplicationPreference::windowSize.y / 2., -0.1, 0.1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
}

void GLSYS::GLBuilder::LightSetup() {
  Scene::LightManager::SetActiveLighting(true);
  Scene::LightManager::Set(
      GL_LIGHT0, PosVec(-100, 50, 100), Color255(0.1f, 0.1f, 0.1f, .5f),
      Color255(1.f, 1.f, 1.f, 1.0f), Color255(1.f, 1.f, 1.f, 1.f));
  Scene::LightManager::SetActive(GL_LIGHT0, true);
  Scene::LightManager::UpdateLight(GL_LIGHT0);

  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
}