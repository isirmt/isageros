#include "SumoScene.hpp"
#include "TitleScene.hpp"

Scene::SumoScene::SumoScene(){
    Camera::SetActive(true);
    SceneBase::SetOrthoCameraWindow();
    Camera::SetAsPerspective(
        ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
        30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    Color255 innerCol;
    innerCol = Color255(255, 100, 50);
    backbutton = new Obj::Button(PosVec(30, 30), PosVec(150, 100), true, true);
    backbutton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backbutton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backbutton->SetInnerAnimation(.2f);

    layer2D.AddObject(backbutton);
}

void Scene::SumoScene::Update(){
    layer2D.Collide();

    if (backbutton->GetMouseSelected()) {
        backbutton->SetMouseOff();
        SceneManager::ChangeScene(new TitleScene());
        return;
    }

    layer2D.Update();
}

void Scene::SumoScene::Draw(){
    SceneBase::Set3DDrawMode();
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    SceneBase::Set2DDrawMode();
    Camera::SetPerspectiveMode(false);
    Camera::UpdateCamera();

    layer2D.Draw();  // 2D描画
}

void Scene::SumoScene::MouseProc(int button, int state, int x, int y) {}