#include <stdio.h>
#include <GL/glut.h>
#include "SceneManager.hpp"
#include "GLBuilder.hpp"
// 最初に呼び出すシーン
#include "TitleScene.hpp"
#include "ApplicationPreference.hpp"
#include "ApplicationBuilder.hpp"

void DisplayProc(), KeyboardProc(unsigned char key , int x , int y), IdleProc(),
MouseProc(int button, int state, int x, int y), MotionProc(int x, int y), PassiveMotionProc(int x, int y); 

int main(int argc, char **argv)
{
    glutInit(&argc , argv);
	glutInitWindowPosition(100 , 50);
	glutInitWindowSize((int)ApplicationPreference::windowSize.x , (int)ApplicationPreference::windowSize.y);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

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

    glutMainLoop();

    return 0;
}