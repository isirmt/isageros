#include <stdio.h>
#include <GL/glut.h>
#include "inc/SceneManager.hpp"
#include "inc/GLBuilder.hpp"
// 最初に呼び出すシーン
#include "inc/TitleScene.hpp"
#include "inc/ApplicationPreference.hpp"

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

    // 関数登録
    glutDisplayFunc(DisplayProc);
    glutKeyboardFunc(KeyboardProc);
    glutIdleFunc(IdleProc);
    glutMouseFunc(MouseProc);
    glutMotionFunc(MotionProc);
    glutPassiveMotionFunc(MotionProc);

    Scene::TitleScene *titleScene = new Scene::TitleScene();
    Scene::SceneManager::ChangeScene(titleScene);

    glutMainLoop();

    return 0;
}