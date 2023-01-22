#include "SumoScene.hpp"
#include "TitleScene.hpp"

Scene::SumoScene::SumoScene(){
    Camera::SetActive(true);
    SceneBase::SetOrthoCameraWindow();
    Camera::SetAsPerspective(
        ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
        30, 1, 99999, PosVec(1000, 1000, 1000), PosVec(0, 0, 0), PosVec(0, 1, 0));
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    stage = Obj::ObjFile(PosVec(60, 5., 0.0), PosVec(), PosVec(), 
                ApplicationPreference::modelFilePath + folderName + "dohyo.obj");
    stage.SetScale(PosVec(100, 100, 100));
    stage.SetShininess(20);
    stage.SetRotate(45, PosVec(0, 1, 0));

    player = Obj::ObjFile(PosVec(465, 201.0, -65.0), PosVec(), PosVec(), 
                ApplicationPreference::modelFilePath + "char/chara.obj");
    player.SetScale(PosVec(5, 5, 5));
    player.SetShininess(10);
    player.SetRotate(-45, PosVec(0, 1, 0));

    enemy = Obj::ObjFile(PosVec(-10.0, 200.0, 410.0), PosVec(), PosVec(), 
                ApplicationPreference::modelFilePath + "char/chara.obj");
    enemy.SetScale(PosVec(5, 5, 5));
    enemy.SetShininess(10);
    enemy.SetRotate(-225, PosVec(0, 1, 0));

    text = new Obj::Text(PosVec(100.0, 500.0), PosVec(), "Let's Play!");
    text->SetInnerColor(Color255(250, 250, 250));

    Color255 innerCol;
    innerCol = Color255(255, 100, 50);
    backbutton = new Obj::Button(PosVec(30, 30), PosVec(150, 100), true, true);
    backbutton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backbutton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backbutton->SetInnerAnimation(.2f);

    innerCol = Color255(70, 170, 230);
    startbutton = new Obj::Button(PosVec(30, 30 + 120), PosVec(150, 100), true, true);
    startbutton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    startbutton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    startbutton->SetInnerAnimation(.2f);
    layer2D.AddObject(startbutton);

    layer2D.AddObject(text);
    layer2D.AddObject(backbutton);
    layer2D.AddObject(startbutton);

    gamestart = false;
}

void Scene::SumoScene::Update(){
    layer2D.Collide();

    stage.Update();
    player.Update();
    enemy.Update();

    if(startbutton->GetMouseSelected()){ 
        startbutton->SetMouseOff();
        gamestart = true;
        startbutton->SetEnabled(false);
        text->SetString("Now Playing.");
    }

    if(gamestart){
        if(player.GetPosition().y > 200.0){
            player.SetPosition(PosVec(265, 200.0, 135.0));
            player.SetVelocity(PosVec(-100.0, 0.0, 100.0));
            enemy.SetPosition(PosVec(190.0, 200.0, 210.0));
            enemy.SetVelocity(PosVec(100.0, 0.0, -100.0));
        } 
        
        if(player.GetPosition().x < enemy.GetPosition().x + 25.0){
            player.SetVelocity(PosVec(10.0, 0.0, -10.0));
            enemy.SetVelocity(PosVec(10.0, 0.0, -10.0));
        }

        if(Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST){
            pushPower += 10.0;
            player.SetVelocity(PosVec(-pushPower, 0.0, pushPower));
            enemy.SetVelocity(PosVec(-pushPower, 0.0, pushPower));

            // gamestart = false;
            // player.SetPosition(PosVec(465, 201.0, -65.0));
            // enemy.SetPosition(PosVec(-10.0, 200.0, 410.0));
            // player.SetVelocity(PosVec(0.0, 0.0, 0.0));
            // enemy.SetVelocity(PosVec(0.0, 0.0, 0.0));
            // text->SetString("Let's play!");
            // startbutton->SetEnabled(true);
        }
    }

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

    glPushMatrix();
    stage.Draw();
    player.Draw();
    enemy.Draw();
    glPopMatrix();

    SceneBase::Set2DDrawMode();
    Camera::SetPerspectiveMode(false);
    Camera::UpdateCamera();

    layer2D.Draw();  // 2D描画
}

void Scene::SumoScene::MouseProc(int button, int state, int x, int y) {}