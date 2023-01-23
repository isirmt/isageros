#include "BattingScene.hpp"

#include "TitleScene.hpp"

Scene::BattingScene::BattingScene(){
    Camera::SetActive(true);
    SceneBase::SetOrthoCameraWindow();
    Camera::SetAsPerspective(
        ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
        30, 100, 2500, PosVec(2000, 1000, 1), PosVec(500, 0, 0), PosVec(0, 1, 0)
    );
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    stage = Obj::ObjFile(PosVec(0.0, 5., 0.0), PosVec(), PosVec(),
                            ApplicationPreference::modelFilePath + folderName +
                                "baseball_stage.obj");
    stage.SetScale(PosVec(100, 100, 100));
    stage.SetShininess(20);
    stage.SetRotate(0, PosVec(0, 1, 0));

    bat = Obj::Cylinder(PosVec(800.0, 80.0, -20.0), PosVec(0.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0));
    bat.SetAmbient(Color255(100, 75, 80));
    bat.SetDiffuse(Color255(.3f, .3f, .3f));
    bat.SetSpecular(Color255(255, 255, 255, 255));
    bat.SetShininess(20);
    bat.SetScale(PosVec(2, 10, 2));

    player = Obj::ObjFile(PosVec(800.0, 0.0, -50.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0), ApplicationPreference::modelFilePath + "char/chara.obj");
    player.SetScale(PosVec(5, 5, 5));
    player.SetShininess(10);

    ball = Obj::Sphere(PosVec(450.0, -50.0, 0.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0));
    ball.SetScale(PosVec(3, 3, 3));
    ball.SetAmbient(Color255(250, 250, 250));
    ball.SetDiffuse(Color255(.3, .3, .3));
    ball.SetSpecular(Color255(0, 0, 0));

    enemy = Obj::ObjFile(PosVec(400.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0), ApplicationPreference::modelFilePath + "char/chara.obj");
    enemy.SetScale(PosVec(5, 5, 5));
    enemy.SetShininess(10);
    enemy.SetRotate(90, PosVec(0, 1, 0));

    flag = false;
    gameStart = false;

    text = new Obj::Text(PosVec(100.0, 500.0), PosVec(),"Baseballgame");
    text->SetInnerColor(Color255(0, 0, 0));
    layer2D.AddObject(text);

    text_2 = new Obj::Text(PosVec(100.0, 475.0), PosVec(),"Now High Score: -");
    text_2->SetInnerColor(Color255(0, 0, 0));
    layer2D.AddObject(text_2);

    Color255 innerCol;
    innerCol = Color255(70, 170, 230);
    startButton = new Obj::Button(PosVec(30, 30 + 120), PosVec(150, 100), true, true);
    startButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    startButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    startButton->SetInnerAnimation(.2f);
    layer2D.AddObject(startButton);

    text_3 = new Obj::Text(PosVec(60.0, 190.0), PosVec(), "Game Start!!");
    text_3->SetInnerColor(Color255(250.0, 250.0, 250.0));
    layer2D.AddObject(text_3);

    innerCol = Color255(255, 100, 50);
    backButton = new Obj::Button(PosVec(30, 30), PosVec(150, 100), true, true);
    backButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backButton->SetInnerAnimation(.2f);
    layer2D.AddObject(backButton);
}

void Scene::BattingScene::Update(){
    layer2D.Collide();

    stage.Update();
    bat.Update();
    player.Update();
    ball.Update();
    enemy.Update();

    if(startButton->GetMouseSelected()){
        startButton->SetMouseOff();
        gameStart = true;
        point = 0;
        strike = 0;
        startButton->SetEnabled(false);
        text->SetString("Point: " + std::to_string(point));
        text_2->SetString("Strike: " + std::to_string(strike));
        text_3->SetString("Fight!!");
    }

    if(gameStart)
    {
    if(ball.GetPosition().y < 50.0){
        ball.SetPosition(PosVec(450.0, 50.0, 0.0));
        ball.SetVelocity(PosVec(300, 0, 0));
    }
    
    if(Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST && flag){
        bat = Obj::Cylinder(PosVec(800.0, 80.0, -20.0), PosVec(0.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0));
        bat.SetAmbient(Color255(100, 75, 80));
        bat.SetDiffuse(Color255(.3f, .3f, .3f));
        bat.SetSpecular(Color255(255, 255, 255, 255));
        bat.SetShininess(20);
        bat.SetScale(PosVec(2, 10, 2));

        flag = false;
    }
    else if(Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST && !flag){
        bat = Obj::Cylinder(PosVec(800.0, 50.0, 5.0), PosVec(0.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0));
        bat.SetAmbient(Color255(100, 75, 80));
        bat.SetDiffuse(Color255(.3f, .3f, .3f));
        bat.SetSpecular(Color255(255, 255, 255, 255));
        bat.SetShininess(20);
        bat.SetScale(PosVec(2, 10, 2));
        bat.SetRotate(45, PosVec(1, 1, 0));

        bat = Obj::Cylinder(PosVec(800.0, 40.0, 10.0), PosVec(0.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0));
        bat.SetAmbient(Color255(100, 75, 80));
        bat.SetDiffuse(Color255(.3f, .3f, .3f));
        bat.SetSpecular(Color255(255, 255, 255, 255));
        bat.SetShininess(20);
        bat.SetScale(PosVec(2, 10, 2));
        bat.SetRotate(90, PosVec(1, 0, 0));

        if(ball.GetPosition().x >= 750.0 && ball.GetPosition().x <= 800.0){
            ball = Obj::Sphere(PosVec(ball.GetPosition()), PosVec(-400.0, 50.0, 0.0), 
                PosVec(0.0, -5.0, 0.0));
            ball.SetScale(PosVec(3, 3, 3));
            ball.SetAmbient(Color255(250, 250, 250));
            ball.SetDiffuse(Color255(.3, .3, .3));
            ball.SetSpecular(Color255(0, 0, 0));
        }

        flag = true;
    }
    
    if(ball.GetPosition().x <= -350.0 || ball.GetPosition().x >= 1200.0){
        if(ball.GetPosition().x >= 1200.0){
            strike++;
            text->SetString("Point: " + std::to_string(point));
            text_2->SetString("Strike: " + std::to_string(strike));
            if(strike >= 3 ){
                high_point = point;
                text->SetString("OUT!");
                text_2->SetString("Now High Score: " + std::to_string(high_point));
                text_3->SetString("Let's Retry!!");

                ball.SetPosition(PosVec(450.0, -50.0, 0.0));
                ball.SetVelocity(PosVec(0, 0, 0));

                gameStart = false;
                startButton->SetEnabled(true);
            }
        }
        else if(ball.GetPosition().x <= -350.0){
            point++;
            text->SetString("Point: " + std::to_string(point));
            text_2->SetString("Strike: " + std::to_string(strike));
        }

        if(strike < 3){
            ball = Obj::Sphere(PosVec(450.0, 50.0, 0.0), PosVec(300.0, 0.0, 0.0), 
                PosVec(0.0, 0.0, 0.0));
            ball.SetScale(PosVec(3, 3, 3));
            ball.SetAmbient(Color255(250, 250, 250));
            ball.SetDiffuse(Color255(.3, .3, .3));
            ball.SetSpecular(Color255(0, 0, 0));
        }
    }
    }

    if (backButton->GetMouseSelected()) {
        backButton->SetMouseOff();
        SceneManager::ChangeScene(new TitleScene());
        return;
    }

    layer2D.Update();
}

void Scene::BattingScene::Draw(){
    SceneBase::Set3DDrawMode();
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    glPushMatrix();
    stage.Draw();
    bat.Draw();
    player.Draw();
    ball.Draw();
    enemy.Draw();
    glPopMatrix();

    SceneBase::Set2DDrawMode();
    Camera::SetPerspectiveMode(false);
    Camera::UpdateCamera();

    layer2D.Draw();
}