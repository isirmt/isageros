#include "SoccerScene.hpp"
#include "StoryScene.hpp"
#include "TitleScene.hpp"

Scene::SoccerScene::SoccerScene() {
    Camera::SetActive(true);
    SceneBase::SetOrthoCameraWindow();
    Camera::SetAsPerspective(
        ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
        30, 1, 9999, PosVec(1700, 1700, 1700), PosVec(0, 0, 0), PosVec(0, 1, 0)
    );
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    stage = Obj::ObjFile(PosVec(200.0, 0.0, 200.0), PosVec(), PosVec(),
            ApplicationPreference::modelFilePath + folderName + "soccer_field.obj");
    stage.SetScale(PosVec(100, 100, 100));
    stage.SetShininess(20);
    stage.SetRotate(-45.0, PosVec(0, 1, 0));

    player = Obj::ObjFile(PosVec(400.0, 0.0, 400.0), PosVec(), PosVec(), 
                ApplicationPreference::modelFilePath + "char/chara.obj");
    player.SetScale(PosVec(10, 10, 10));
    player.SetShininess(10);
    player.SetRotate(225, PosVec(0, 1, 0));

    enemy = Obj::ObjFile(PosVec(-200.0, 0.0, -200.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0), ApplicationPreference::modelFilePath + "char/chara.obj");
    enemy.SetScale(PosVec(10, 10, 10));
    enemy.SetShininess(10);
    enemy.SetRotate(45, PosVec(0, 1, 0));

    Color255 innerCol;
    innerCol = Color255(255, 100, 50);
    backbutton = new Obj::Button(PosVec(30, 30), PosVec(150, 100), true, true);
    backbutton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backbutton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backbutton->SetInnerAnimation(.2f);
    layer2D.AddObject(backbutton);

    text = new Obj::Text(PosVec(100.0, 500.0), PosVec(),"Rumdum Number");
    text->SetInnerColor(Color255(0, 0, 0));
    layer2D.AddObject(text);

    //乱数定義
    srand((unsigned int)time(NULL));
}

void Scene::SoccerScene::Update() {
    layer2D.Collide();

    stage.Update();
    player.Update();
    enemy.Update();

    if(Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST){
        ransu = 0 + rand() % 3;
        if(ransu == 0){
            enemy.SetPosition(PosVec(-200.0, 0.0, -200.0));
            text->SetString("Rumdum Number : " + std::to_string(ransu));
        }
        else if(ransu == 1){
            enemy.SetPosition(PosVec(-50.0, 0.0, -350.0));
            text->SetString("Rumdum Number : " + std::to_string(ransu));
        }
        else if(ransu == 2){
            enemy.SetPosition(PosVec(-350.0, 0.0, -50.0));
            text->SetString("Rumdum Number : " + std::to_string(ransu));
        }
    }

    if (backbutton->GetMouseSelected()) {
        backbutton->SetMouseOff();
        SceneManager::ChangeScene(new TitleScene());
        return;
    }

    layer2D.Update();
}
void Scene::SoccerScene::Draw() {
    SceneBase::Set3DDrawMode();
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    glPushMatrix();
    stage.Draw();
    player.Draw();
    enemy.Draw();
    glPopMatrix();

    SceneBase::Set2DDrawMode();
    Camera::SetPerspectiveMode(false);
    Camera::UpdateCamera();

    layer2D.Draw();
}