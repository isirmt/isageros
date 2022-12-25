#include <GL/glut.h>
#include <stdio.h>

#include "ApplicationBuilder.hpp"
#include "SceneManager.hpp"

void DisplayProc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glPushMatrix();
  Scene::SceneManager::GetCurrentScene()->Draw();
  glPopMatrix();
  glutSwapBuffers();
}

void KeyboardProc(unsigned char key, int x, int y) {
  printf("Key = %c\n", key);
  Scene::SceneManager::GetCurrentScene()->KeyboardProc(key, x, y);
  glutPostRedisplay();
}

void IdleProc() {
  GLSYS::ApplicationBuilder::Update();
  Scene::SceneManager::GetCurrentScene()->Update();
  glutPostRedisplay();
}

void MouseProc(int button, int state, int x, int y) {
  Scene::SceneManager::GetCurrentScene()->MouseProc(button, state, x, y);
  glutPostRedisplay();
}

void MotionProc(int x, int y) {
  Scene::SceneManager::GetCurrentScene()->MotionProc(x, y);
  glutPostRedisplay();
}

void PassiveMotionProc(int x, int y) {
  Scene::SceneManager::GetCurrentScene()->PassiveMotionProc(x, y);
  glutPostRedisplay();
}