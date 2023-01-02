#include "GLBuilder.hpp"

void GLSYS::GLBuilder::GLSetup() {
  glClearColor(ApplicationPreference::defaultWorldColor.r,
               ApplicationPreference::defaultWorldColor.g,
               ApplicationPreference::defaultWorldColor.b, 0.0);
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // glOrtho(-800, 800.0, -450.0, 450.0, -800.0, 800.0);
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

  // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  // glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  // glLightfv(GL_LIGHT0, GL_POSITION, position);

  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  // glEnable(GL_COLOR_MATERIAL);
}