#include <GL/glut.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "GLBuilder.hpp"
#include "SceneManager.hpp"
// 最初に呼び出すシーン
#include "ApplicationBuilder.hpp"
#include "ApplicationPreference.hpp"
#include "ObjectLoader.hpp"
#include "TitleScene.hpp"
#include "LaunchLogoScene.hpp"

void DisplayProc(), KeyboardProc(unsigned char key, int x, int y), IdleProc(),
    MouseProc(int button, int state, int x, int y), MotionProc(int x, int y),
    PassiveMotionProc(int x, int y), WindowResizeProc(int width, int height), CloseFunc();

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 50);
  glutInitWindowSize((int)ApplicationPreference::windowSize.x,
                     (int)ApplicationPreference::windowSize.y);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutCreateWindow("ISAGEROS");

  GLSYS::GLBuilder::GLSetup();
  GLSYS::GLBuilder::LightSetup();
  GLSYS::ApplicationBuilder::Initialize();

  // 関数登録
  glutDisplayFunc(DisplayProc);
  glutReshapeFunc(WindowResizeProc);
  glutKeyboardFunc(KeyboardProc);
  glutIdleFunc(IdleProc);
  glutMouseFunc(MouseProc);
  glutMotionFunc(MotionProc);
  glutPassiveMotionFunc(MotionProc);
  glutCloseFunc(CloseFunc);

  Scene::LaunchLogoScene *launchLogoScene = new Scene::LaunchLogoScene();
  Scene::SceneManager::ChangeScene(launchLogoScene);

  glutMainLoop();

  return 0;
}