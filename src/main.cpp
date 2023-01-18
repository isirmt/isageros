#include <GL/glut.h>
#include <stdio.h>

#include "GLBuilder.hpp"
#include "SceneManager.hpp"
// 最初に呼び出すシーン
#include "ApplicationBuilder.hpp"
#include "ApplicationPreference.hpp"
#include "ArcheryScene.hpp"
#include "ObjectLoader.hpp"
#include "TitleScene.hpp"

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

  ArcheryScene::GameScene *gameScene = new ArcheryScene::GameScene();
  Scene::SceneManager::ChangeScene(gameScene);

  Scene::TitleScene *titleScene = new Scene::TitleScene();
  Scene::SceneManager::ChangeScene(titleScene);

  glutMainLoop();

  return 0;
}