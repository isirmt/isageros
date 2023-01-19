#include "BattingScene.hpp"

Scene::BattingScene::BattingScene(){
    Camera::SetActive(true);
    SceneBase::SetOrthoCameraWindow();
    Camera::SetAsPerspective(
        ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
        30, 100, 2500, PosVec(2000, 1000, 1), PosVec(500, 0, 0), PosVec(0, 1, 0)
    );
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    centerCube = Obj::ObjFile(PosVec(0.0, 5., 0.0), PosVec(), PosVec(),
                            ApplicationPreference::modelFilePath + folderName +
                                "baseball_stage.obj");
    centerCube.SetScale(PosVec(100, 100, 100));
    centerCube.SetShininess(20);
    centerCube.SetRotate(0, PosVec(0, 1, 0));
}

void Scene::BattingScene::Update(){
    centerCube.Update();
}

void Scene::BattingScene::Draw(){
    SceneBase::Set3DDrawMode();
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    glPushMatrix();
    centerCube.Draw();
    glPopMatrix();

    SceneBase::Set2DDrawMode();
    Camera::SetPerspectiveMode(false);
    Camera::UpdateCamera();
}