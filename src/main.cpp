#include <stdio.h>
#include <GL/glut.h>
#include "inc/Color255.hpp"
#include "inc/SceneManager.hpp"
#include "inc/TitleScene.hpp"

int main(int argc, char** argv)
{
    Color255 col;
    col = Color255("#2549C4");
    printf("%f, %f, %f, %f\n", col.r, col.g, col.b, col.a);
    col = Color255("141414");
    printf("%f, %f, %f, %f\n", col.r, col.g, col.b, col.a);
    col = Color255(253,45,32,25);
    printf("%f, %f, %f, %f\n", col.r, col.g, col.b, col.a);

    Scene::TitleScene *titleScene = new Scene::TitleScene();
    Scene::SceneManager::ChangeScene(titleScene);

    Scene::SceneManager::Update();

    return 0;
}