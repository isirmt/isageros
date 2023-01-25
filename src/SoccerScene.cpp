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

    null = new Obj::Null();
    layer2D.AddObject(null);

    stage = Obj::ObjFile(PosVec(200.0, 0.0, 200.0), PosVec(), PosVec(),
            ApplicationPreference::modelFilePath + folderName + "soccer_field.obj");
    stage.SetScale(PosVec(100, 100, 100));
    stage.SetShininess(20);
    stage.SetRotate(-45.0, PosVec(0, 1, 0));

    player = Obj::ObjFile(PosVec(565.0, 0.0, 565.0), PosVec(), PosVec(), 
                ApplicationPreference::modelFilePath + "char/chara.obj");
    player.SetScale(PosVec(10, 10, 10));
    player.SetShininess(10);
    player.SetRotate(225, PosVec(0, 1, 0));

    enemy = Obj::ObjFile(PosVec(-200.0, 0.0, -200.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0), ApplicationPreference::modelFilePath + "char/chara.obj");
    enemy.SetScale(PosVec(10, 10, 10));
    enemy.SetShininess(10);
    enemy.SetRotate(45, PosVec(0, 1, 0));
    
    ball = Obj::Sphere(PosVec(400.0, 35.1, 400.0), PosVec(), PosVec());
    ball.SetScale(PosVec(7, 7, 7));
    ball.SetAmbient(Color255(250, 250, 250));
    ball.SetDiffuse(Color255(.3, .3, .3));
    ball.SetSpecular(Color255(0, 0, 0));

    Color255 innerCol;
    innerCol = Color255(255, 100, 50);
    backbutton = new Obj::Button(PosVec(30, 30), PosVec(150, 100), true, true);
    backbutton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backbutton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backbutton->SetInnerAnimation(.2f);
    layer2D.AddObject(backbutton);

    innerCol = Color255(70, 170, 230);
    startButton = new Obj::Button(PosVec(30, 30 + 120), PosVec(150, 100), true, true);
    startButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    startButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    startButton->SetInnerAnimation(.2f);
    layer2D.AddObject(startButton);

    text = new Obj::Text(PosVec(100.0, 500.0), PosVec(),"Let's Play!");
    text->SetInnerColor(Color255(0, 0, 0));
    layer2D.AddObject(text);

    text_2 = new Obj::Text(PosVec(100.0, 475.0), PosVec(),"");
    text->SetInnerColor(Color255(0, 0, 0));
    layer2D.AddObject(text_2);

    //乱数定義
    srand((unsigned int)time(NULL));
    gameStart = false;
    point = 0;
    shootCount = 0;
}

void Scene::SoccerScene::Update() {
    layer2D.Collide();

    stage.Update();
    player.Update();
    enemy.Update();
    ball.Update();

    if(startButton->GetMouseSelected()){
        startButton->SetMouseOff();
        gameStart = true;
        startButton->SetEnabled(false);

        if(shootCount == 0) point = 0;
        ball.SetPosition(PosVec(400.0, 35.1, 400.0));
        text->SetString("Where do you shoot?");
        text_2->SetString("Point : " + std::to_string(point));

        Color255 innerCol;
        innerCol = Color255(70, 170, 230);
        centerButton = new Obj::Button(PosVec(620, 30), PosVec(50, 50), true, true);
        centerButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
        centerButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
        centerButton->SetInnerAnimation(.2f);
        layer2D.AddObject(centerButton);

        innerCol = Color255(70, 170, 230);
        rightButton = new Obj::Button(PosVec(870, 30), PosVec(50, 50), true, true);
        rightButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
        rightButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
        rightButton->SetInnerAnimation(.2f);
        layer2D.AddObject(rightButton);

        innerCol = Color255(70, 170, 230);
        leftButton = new Obj::Button(PosVec(370, 30), PosVec(50, 50), true, true);
        leftButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
        leftButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
        leftButton->SetInnerAnimation(.2f);
        layer2D.AddObject(leftButton);

        threeMouseCondition(true);
    }

    if(gameStart){
        if(centerButton->GetMouseSelected()){
            threeMouseCondition(false);
            ball.SetVelocity(PosVec(-400.0, 0.0, -400.0));
            text->SetString("Shoot!!");
            KeeperPosition();
        }
        else if(rightButton->GetMouseSelected()){
            threeMouseCondition(false);
            ball.SetVelocity(PosVec(-240.0, 0.0, -400.0));
            text->SetString("Shoot!!");
            KeeperPosition();
        }
        else if(leftButton->GetMouseSelected()){
            threeMouseCondition(false);
            ball.SetVelocity(PosVec(-400.0, 0.0, -240.0));
            text->SetString("Shoot!!");
            KeeperPosition();
        }

        if((ball.GetPosition().x <= (enemy.GetPosition().x + 10.0) && 
            ball.GetPosition().z <= (enemy.GetPosition().z + 10.0)) || 
            ball.GetPosition().x <= -500.0 || ball.GetPosition().z <= -500.0){
                ball.SetVelocity(PosVec(0.0, 0.0, 0.0));
                if(ball.GetPosition().x <= enemy.GetPosition().x || 
                    ball.GetPosition().z <= enemy.GetPosition().z){
                    point++;
                    text->SetString("Goal!!");
                    text_2->SetString("Point : " + std::to_string(point));
                }
                else{
                    text->SetString("Saved...");
                    text_2->SetString("Point : " + std::to_string(point));
                }

                shootCount++;
                if(shootCount >= 5){
                    if(point >= 3){
                        text->SetString("Winner!");
                    }
                    else{
                        text->SetString("Lose...");
                    }
                    shootCount = 0;
                }

                gameStart = false;
                startButton->SetEnabled(true);
            }
    }

    if (backbutton->GetMouseSelected()) {
        backbutton->SetMouseOff();
        SceneManager::ChangeScene(new TitleScene());
        return;
    }

    layer2D.Update();
}

void Scene::SoccerScene::KeeperPosition(){
    ransu = 0 + rand() % 3;
    if(ransu == 0){
        // enemy.SetPosition(PosVec(-200.0, 0.0, -200.0));
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->x, -200, 3.f);
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->z, -200, 3.f);
    }
    else if(ransu == 1){
        // enemy.SetPosition(PosVec(-50.0, 0.0, -350.0));
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->x, -50, 3.f);
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->z, -350, 3.f);
    }
    else if(ransu == 2){
        // enemy.SetPosition(PosVec(-350.0, 0.0, -50.0));
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->x, -350, 3.f);
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->z, -50, 3.f);
    }
}

void Scene::SoccerScene::threeMouseCondition(bool x){
    if(x){
        centerButton->SetEnabled(true);
        rightButton->SetEnabled(true);
        leftButton->SetEnabled(true);
    }
    else{
        centerButton->SetMouseOff();
        centerButton->SetEnabled(false);
        rightButton->SetMouseOff();
        rightButton->SetEnabled(false);
        leftButton->SetMouseOff();
        leftButton->SetEnabled(false);
    }
}

void Scene::SoccerScene::Draw() {
    SceneBase::Set3DDrawMode();
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    glPushMatrix();
    stage.Draw();
    player.Draw();
    enemy.Draw();
    ball.Draw();
    glPopMatrix();

    SceneBase::Set2DDrawMode();
    Camera::SetPerspectiveMode(false);
    Camera::UpdateCamera();

    layer2D.Draw();
}