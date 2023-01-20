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

    ball = Obj::Sphere(PosVec(450.0, 50.0, 0.0), PosVec(100.0, 0.0, 0.0), 
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

    // text = new Obj::Text(PosVec(900.0, 100.0, 100.0), PosVec(100, 100, 100),
    //                    "テーブルテニス 卓球 Table_Tennis\nサンプルテキスト");
    // text->SetInnerColor(Color255(250, 250, 250));
    // layer2D.AddObject(text);
}

void Scene::BattingScene::Update(){
    layer2D.Collide();

    stage.Update();
    bat.Update();
    player.Update();
    ball.Update();
    enemy.Update();

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

        if(ball.GetPosition().x >= 780.0 && ball.GetPosition().x <= 820.0){
            ball = Obj::Sphere(PosVec(ball.GetPosition()), PosVec(-100.0, 50.0, 0.0), 
                PosVec(0.0, -5.0, 0.0));
            ball.SetScale(PosVec(3, 3, 3));
            ball.SetAmbient(Color255(250, 250, 250));
            ball.SetDiffuse(Color255(.3, .3, .3));
            ball.SetSpecular(Color255(0, 0, 0));
        }

        flag = true;
    }
    
    if(ball.GetPosition().x <= -350.0 || ball.GetPosition().x >= 1200.0){
        ball = Obj::Sphere(PosVec(450.0, 50.0, 0.0), PosVec(100.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0));
        ball.SetScale(PosVec(3, 3, 3));
        ball.SetAmbient(Color255(250, 250, 250));
        ball.SetDiffuse(Color255(.3, .3, .3));
        ball.SetSpecular(Color255(0, 0, 0));
    }
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