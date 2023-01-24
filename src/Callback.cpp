#include <GL/glut.h>
#include <stdio.h>

#include "ApplicationBuilder.hpp"
#include "GLBuilder.hpp"
#include "MouseInput.hpp"
#include "SceneManager.hpp"

void DisplayProc() {
  GLSYS::GLBuilder::DrawInitialize();
  glPushMatrix();
  Scene::SceneManager::GetCurrentScene()->Draw();
  glPopMatrix();
  glutSwapBuffers();
}

void KeyboardProc(unsigned char key, int x, int y) {
  Scene::SceneManager::GetCurrentScene()->KeyboardProc(key, x, ApplicationPreference::windowSize.y - y);
  glutPostRedisplay();
}

void IdleProc() {
  GLSYS::ApplicationBuilder::Update();
  Scene::SceneManager::GetCurrentScene()->Update();
  glutPostRedisplay();
}

void MouseProc(int button, int state, int x, int y) {
  Scene::SceneManager::GetCurrentScene()->MouseProc(button, state, x, ApplicationPreference::windowSize.y - y);
  Input::MouseInput::UpdateMouseState(button, state);
  Input::MouseInput::SetMousePos(
      PosVec(x, ApplicationPreference::windowSize.y - y));
  glutPostRedisplay();
}

void MotionProc(int x, int y) {
  Scene::SceneManager::GetCurrentScene()->MotionProc(x, ApplicationPreference::windowSize.y - y);
  Input::MouseInput::SetMousePos(
      PosVec(x, ApplicationPreference::windowSize.y - y));
  glutPostRedisplay();
}

void PassiveMotionProc(int x, int y) {
  Scene::SceneManager::GetCurrentScene()->PassiveMotionProc(x, ApplicationPreference::windowSize.y - y);
  Input::MouseInput::SetMousePos(
      PosVec(x, ApplicationPreference::windowSize.y - y));
  glutPostRedisplay();
}