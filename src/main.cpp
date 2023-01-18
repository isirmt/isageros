#include <GL/glut.h>
#include <stdio.h>

#include "GLBuilder.hpp"
#include "SceneManager.hpp"
// 最初に呼び出すシーン
#include "ApplicationBuilder.hpp"
#include "ApplicationPreference.hpp"
#include "ArcheryScene.hpp"
#include "ObjectLoader.hpp"
#include "TableTennisScene.hpp"

void DisplayProc(), KeyboardProc(unsigned char key, int x, int y), IdleProc(),
    MouseProc(int button, int state, int x, int y), MotionProc(int x, int y),
    PassiveMotionProc(int x, int y);

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 50);
  glutInitWindowSize((int)ApplicationPreference::windowSize.x,
                     (int)ApplicationPreference::windowSize.y);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutCreateWindow("Mini Games");

  GLSYS::GLBuilder::GLSetup();
  GLSYS::GLBuilder::LightSetup();
  GLSYS::ApplicationBuilder::Initialize();

  // 関数登録
  glutDisplayFunc(DisplayProc);
  glutKeyboardFunc(KeyboardProc);
  glutIdleFunc(IdleProc);
  glutMouseFunc(MouseProc);
  glutMotionFunc(MotionProc);
  glutPassiveMotionFunc(MotionProc);

  Scene::ArcheryScene *archeryScene = new Scene::ArcheryScene();
  Scene::SceneManager::ChangeScene(archeryScene);
  Scene::TableTennisScene *tableTennisScene = new Scene::TableTennisScene();
  Scene::SceneManager::ChangeScene(tableTennisScene);

  glutMainLoop();

  return 0;
}