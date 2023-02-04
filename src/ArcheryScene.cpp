#include "ArcheryScene.hpp"

#include "StoryScene.hpp"
#include "TitleScene.hpp"
#include <stdio.h>
#include <cmath>

Scene::ArcheryScene::ArcheryScene(){
    Camera::SetActive(true);
  	SceneBase::SetOrthoCameraWindow();
  	Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(1000.0, 200.0, 0.0), centerCube.GetPosition(), PosVec(0,1,0));
  	Camera::SetPerspectiveMode(true);
  	Camera::UpdateCamera();
    deg = 90.f;
    arrow = Obj::ObjFile(PosVec(948.0, 195.0, -8.0), PosVec(),
                       PosVec(),ApplicationPreference::modelFilePath + folderName +
                                "archery_arrow.obj");
    arrow.SetShininess(20);
    arrow.SetScale(PosVec(3, 1, 1));
    arrow.SetMultiRotates(true);
    
    bow = Obj::ObjFile(PosVec(967.0, 195.0, -9.0), PosVec(),
                       PosVec(),ApplicationPreference::modelFilePath + folderName +
                                "archery_bow.obj");
    bow.SetShininess(20);
    bow.SetScale(PosVec(1, 2, 1));

    cube = Obj::Cube(PosVec(-40.0, 10., 0.0), PosVec(500, 7, 0.0),
                   PosVec(0, -300, 0.0));
    cube.SetAmbient(Color255(100, 75, 80));
    cube.SetDiffuse(Color255(.3f, .3f, .3f));
    cube.SetSpecular(Color255(255, 255, 255, 255));
    cube.SetScale(PosVec(10, 10, 10));
    cube.SetShininess(20);
    cube.SetRotate(30, PosVec(.5, .7, 0));

    centerCube = Obj::Cylinder(PosVec(-1000.0, 150.0, 0.0), PosVec(), PosVec());
    centerCube.SetAmbient(Color255(114, 235, 209));
    centerCube.SetDiffuse(Color255(.3f, .3f, .3f));
    centerCube.SetSpecular(Color255(1.f, 1.f, 1.f, 1.f));
    centerCube.SetScale(PosVec(10, 10, 10));
    centerCube.SetShininess(20);
    centerCube.SetRotate(90, PosVec(0, 0, 1));

    stage = Obj::ObjFile(PosVec(0.0, 0.0, 0.0), PosVec(), PosVec(),
                            ApplicationPreference::modelFilePath + folderName +
                                "archery_stage.obj");
    stage.SetScale(PosVec(100, 100, 100));
    stage.SetShininess(20);
    stage.SetRotate(90, PosVec(0, 0, 0));

    Scene::LightManager::Set(
      GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
      Color255(1.f, 1.f, 1.f, 1.0f), Color255(0.0f, 0.0f, 0.0f, 1.f));

    flag = false;
    gameStart = false;
    ruleView = false;


    isShooting = false;
    timerCount = timerCountMax;
    miniuiImage = new Obj::Image(
        PosVec(0, 30), PosVec(75, 190),
        ApplicationPreference::imgFilePath + "minigames/miniui.ppm");
    layer2D.AddObject(miniuiImage);

    Color255 innerCol;
    innerCol = Color255(70, 170, 230);
    startButton = new Obj::Button(PosVec(30, 100), PosVec(50, 50), true, true);
    startButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    startButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    startButton->SetInnerAnimation(.2f);
    layer2D.AddObject(startButton);

    innerCol = Color255(255, 100, 50);
    backButton = new Obj::Button(PosVec(30, 30), PosVec(50, 50), true, true);
    backButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backButton->SetInnerAnimation(.2f);
    layer2D.AddObject(backButton);

    innerCol = Color255("#57B7F3");
    rect = new Obj::Rectangle(PosVec(0, 0), PosVec(50, 50), true, false);
    rect->SetInnerColor(innerCol);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x, 0.f, 10.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y, 0.f, 10.f);
    layer2D.AddObject(rect);

    nImage = new Obj::Image(ruleImageOffset, ruleImageSize,
                ApplicationPreference::imgFilePath + "minigames/gameover.ppm");
                rulePics.emplace_back(nImage);
    nImage = new Obj::Image(
        ruleImageOffset, ruleImageSize,
        ApplicationPreference::imgFilePath + "minigames/quotaAc.ppm");
    rulePics.emplace_back(nImage);
    nImage = new Obj::Image(
        ruleImageOffset, ruleImageSize,
        ApplicationPreference::imgFilePath + "minigames/quotaAc.ppm");
    rulePics.emplace_back(nImage);

    innerCol = Color255("7894DA");
    ruleBack =
        new Obj::Rectangle(PosVec(ruleImageOffset.x - 5, ruleImageOffset.y - 5),
                            PosVec(ruleImageSize.x + 10, ruleImageSize.y + 30));
    ruleBack->SetInnerColor(innerCol);

    ruleText = new Obj::Text(
        PosVec(ruleImageOffset.x + 5.f, ruleImageOffset.y + ruleImageSize.y + 3),
        PosVec(), "ルール説明：次へは画像をクリック！・戻る場合は「ルール」ボタン");
    ruleText->SetInnerColor(Color255(250));

    innerCol = Color255(70, 100, 230);
    ruleButton = new Obj::Button(PosVec(30, 30 + (50 + 20) * 2), PosVec(50, 50), true, true);
    ruleButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    ruleButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    ruleButton->SetInnerAnimation(.2f);
    layer2D.AddObject(ruleButton);

    innerCol = Color255(70, 170, 230);
    textBack = new Obj::Rectangle(
        PosVec(100, 30), PosVec(ApplicationPreference::windowSize.x - 150, 30));
    textBack->SetInnerColor(innerCol);
    layer2D.AddObject(textBack);

    text = new Obj::Text(PosVec(110, 35), PosVec(), 
                "ボタンをクリックして開始：ストーリーノルマ(" + std::to_string(clearScore) + ")");
    text->SetInnerColor(Color255(250.0, 250.0, 250.0));
    layer2D.AddObject(text);
    layer2D.AddObject(backButton);

    innerCol = Color255("#57B7F3");
    rect = new Obj::Rectangle(PosVec(0, 0), PosVec(50, 50), true, false);
    rect->SetInnerColor(innerCol);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x, 0.f, 10.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y, 0.f, 10.f);
    layer2D.AddObject(rect);

    goRect = new Obj::Image(
        PosVec(ApplicationPreference::windowSize.x / 2.f, -100), PosVec(0, 0),
        ApplicationPreference::imgFilePath + "minigames/gameover.ppm");

    innerCol = Color255("#57B7F3");
    quotaImage = new Obj::Image(
        PosVec(-500, 450), PosVec(150, 100),
        ApplicationPreference::imgFilePath + "minigames/quotaAc.ppm");
}

void Scene::ArcheryScene::Update(){
  layer2D.Collide();

  arrow.Update();
  centerCube.Update();
  stage.Update();
  bow.Update();


  if(startButton->GetMouseSelected()){
        startButton->SetMouseOff();
        gameStart = true;
        
        point = 0;
        turn = 1;
        startButton->SetEnabled(false);
        ruleButton->SetEnabled(false);
        text->SetString("得点：" + std::to_string(point) + "  " + 
                                 std::to_string(turn) + "射目");

        ruleView = false;
        RuleMode();

        goRect->ChangeValueWithAnimation(
            &goRect->GetVectorPointer(VectorType::SIZE)->x, 1, .3f);
        goRect->ChangeValueWithAnimation(
            &goRect->GetVectorPointer(VectorType::SIZE)->y, 1, .3f);
        goRect->ChangeValueWithAnimation(
            &goRect->GetVectorPointer(VectorType::POS)->x,
            ApplicationPreference::windowSize.x / 2.f, .3f);
        goRect->ChangeValueWithAnimation(
            &goRect->GetVectorPointer(VectorType::POS)->y, -100.f, .3f);
    }

    if(ruleButton->GetMouseSelected()){
        ruleButton->SetMouseOff();
        ruleView = !ruleView;   
        RuleMode();
    }
    if (ruleView) {
        int i = 0;
        for (auto& item : rulePics) {
            if (item->GetMouseSelected()) {
                item->SetMouseOff();
                layer2D.DeleteObject(item);
                if (i == rulePics.size() - 1) {
                layer2D.AddObject(rulePics[0]);
                } else {
                layer2D.AddObject(rulePics[i + 1]);
                }
            }
            i++;
        }
    }
  
  if(gameStart)
  {
    if (goRect->GetPos().y < -70) layer2D.DeleteObject(goRect);
    PosVec ends[4] = {
    PosVec(-1000.0, 300.0, 600.0),
    PosVec(-1000.0, 300.0, -600.0),
    PosVec(-1000.0,   0.0, -600.0),
    PosVec(-1000.0,   0.0, 600.0)};
    
  
    
  if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) >= PressFrame::FIRST && !isShooting) {
    Mouseflag = true;
    arrow.SetMultiRotates(true);
    Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      10, 1, 99999, PosVec(1000.0, 200.0, 0.0), 
      PosVec(centerCube.GetPosition().x,
      (Input::MouseInput::GetMouse().y/ApplicationPreference::windowSize.y)*ends[0].y,
      (((Input::MouseInput::GetMouse().x/ApplicationPreference::windowSize.x)*ends[1].z*2)-ends[1].z)), 
      PosVec(0,1,0));
    Camera::UpdateCamera();
    RotY =  180.f - 90.f - 55.f - 70.f / ApplicationPreference::windowSize.x * Input::MouseInput::GetMouse().x;
    RotZ =  20.f - 40.f / ApplicationPreference::windowSize.y * Input::MouseInput::GetMouse().y;
    const float leftDeg = 10;
    const float rightDeg = 10;
    std:: cout << RotY << "," << rightDeg << std::endl;
    arrow.ClearRotates(); 
    arrow.AddMultiRotates(RotY, PosVec(0,1,0));
    arrow.AddMultiRotates(RotZ, PosVec(0,0,1));
  }
  else if((Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::ZERO && Mouseflag) || isShooting ){
    if (!isShooting) {
      arrow.SetPosition(arrow.GetPosition());
      arrow.SetVelocity(
        PosVec(
          -1500.0 * cos(RotY * M_PI / 180.f),
          -1500.0 * sin(RotZ * M_PI / 180.f),
          1500.f * sin(RotY * M_PI / 180.f)));
      arrow.SetAcceleration(PosVec(0.0, -200.0, 0.0));
      arrow.AddMultiRotates(0.1, PosVec(0,0,1));
      isShooting = true;
    }

    // z -60 ~ 60
    // (y,z) = (100,0)が中央
    // y 60 ~ 160
    
    Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(
        arrow.GetPosition().x+100,
        arrow.GetPosition().y+1,arrow.GetPosition().z+1),
        arrow.GetPosition(), PosVec(0,1,0));
    Camera::UpdateCamera();
    printf("%f,%f,%f\n",arrow.GetPosition().x,arrow.GetPosition().y,arrow.GetPosition().z);
    if(arrow.GetPosition().x <= -750 || arrow.GetPosition().y <= 20){
      if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=6.0){
        point10=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=12.0){
        point9=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=18.0){
        point8=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=24.0){
        point7=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=30.0){
        point6=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=36.0){
        point5=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=42.0){
        point4=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=48.0){
        point3=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=54.0){
        point2=true;
      }else if(sqrt(pow((arrow.GetPosition().y-100.0),2)+pow(arrow.GetPosition().z,2))<=60.0){
        point1=true;
      }
      // 的の座標内か
      arrow.SetPosition(arrow.GetPosition());
      arrow.SetVelocity(PosVec());
      arrow.SetAcceleration(PosVec());
      //arrow.AddMultiRotates(0, PosVec(0,0,1));
      //arrow.ClearRotates();
      timerCount -= Time::DeltaTime();
      if (timerCount <= 0.f) {
        if(point1){
          point++;
          point1 = !point1;
        }else if(point2){
          point = point + 2;
          point2 = !point2;
        }else if(point3){
          point = point + 3;
          point3 = !point3;
        }else if(point4){
          point = point + 4;
          point4 = !point4;
        }else if(point5){
          point = point + 5;
          point5 = !point5;
        }else if(point6){
          point = point + 6;
          point6 = !point6;
        }else if(point7){
          point = point + 7;
          point7 = !point7;
        }else if(point8){
          point = point + 8;
          point8 = !point8;
        }else if(point9){
          point = point + 9;
          point9 = !point9;
        }else if(point10){
          point = point + 10;
          point10 = !point10;
        }
        timerCount = timerCountMax;
        arrow = Obj::ObjFile(PosVec(948.0, 195.0, -8.0), PosVec(),
                       PosVec(),ApplicationPreference::modelFilePath + folderName +
                                "archery_arrow.obj");
    		arrow.SetShininess(20);
    		arrow.SetScale(PosVec(3, 1, 1));
    		//arrow.ClearRotates();
    		RotY = 0.f;
    		RotZ = 0.f;
        turn++;
        text->SetString("得点：" + std::to_string(point) + "  " + 
                                 std::to_string(turn) + "射目");
        if(turn>3){
        	gameStart = false;
          startButton->SetEnabled(true);
          ruleButton->SetEnabled(true);
          Camera::SetAsPerspective(
      			ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      			30, 1, 99999, PosVec(1000.0, 200.0, 0.0), centerCube.GetPosition(), PosVec(0,1,0));
    			Camera::UpdateCamera();
    			text->SetString("得点：" + std::to_string(point) + "  " + 
                                 "お疲れ様でした。");
        	if(point >= clearScore && Story::StoryModeManager::GetGameActive()){
        						text->SetString("得点：" + std::to_string(point) + "  " + 
                                 "クリア！");
                    Story::StoryModeManager::SetGameClear(true);
                    Story::StoryModeManager::SavePlusStep();
                    layer2D.DeleteObject(quotaImage);
                    layer2D.AddObject(quotaImage);
                    startButton->SetEnabled(false);
                    ruleButton->SetEnabled(false);
                    quotaImage->ChangeValueWithAnimation(
                        &quotaImage->GetVectorPointer(VectorType::POS)->x, 30, 3.f);
                    
                }
                else if(Story::StoryModeManager::GetGameActive()){
                		text->SetString("得点：" + std::to_string(point) + "  " + 
                                 "ゲームオーバー");
                    Story::StoryModeManager::SetGameClear(false);
                }//終わる
        }
        Mouseflag = false;
        isShooting = false;
      }
    }
  }else{
    Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(1000.0, 200.0, 0.0), centerCube.GetPosition(), PosVec(0,1,0));
    Camera::UpdateCamera();
  }
    
  arrow.Update();
  centerCube.Update();
  stage.Update();
  bow.Update();

  layer2D.Collide();

  }

  if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) >= PressFrame::FIRST) {
    PosVec markSize(50, 50);
    rect->SetPos(PosVec(Input::MouseInput::GetMouse().x - markSize.x / 2.f,
                        Input::MouseInput::GetMouse().y - markSize.y / 2.f));
    rect->SetSize(markSize);
    rect->ChangeValueWithAnimation(
        &rect->GetVectorPointer(VectorType::POS)->x,
        Input::MouseInput::GetMouse().x - markSize.x / 2.f, 5.f);
    rect->ChangeValueWithAnimation(
        &rect->GetVectorPointer(VectorType::POS)->y,
        Input::MouseInput::GetMouse().y - markSize.y / 2.f, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x,
                                   1.f, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y,
                                   1.f, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::POS)->x,
                                   Input::MouseInput::GetMouse().x, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::POS)->y,
                                   Input::MouseInput::GetMouse().y, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x,
                                   0.f, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y,
                                   0.f, 5.f);
    }

    layer2D.Update();
  

  if (backButton->GetMouseSelected()) {
        backButton->SetMouseOff();
        if(!Story::StoryModeManager::GetGameActive()){
            SceneManager::ChangeScene(new TitleScene());
        }
        else{
            Story::StoryModeManager::SetGameActive(false);
            SceneManager::ChangeScene(new StoryScene());
        }
        return;
    }
}

void Scene::ArcheryScene::RuleMode(){
    if(ruleView){
        if(rulePics.size() != 0){
            layer2D.AddObject(ruleBack);
            layer2D.AddObject(ruleText);
            layer2D.AddObject(rulePics[0]);
        }
        else{
            ruleView = false;
        }
    }
    else{
        for (auto& item : rulePics) {
            layer2D.DeleteObject(item);
        }
        layer2D.DeleteObject(ruleBack);
        layer2D.DeleteObject(ruleText);
    }
}

void Scene::ArcheryScene::Draw(){
	SceneBase::Set3DDrawMode();
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  glPushMatrix(); // 3D描画
  {
    glPushMatrix();
    arrow.Draw();
    glPopMatrix();
  }
  //arrow.Draw();
  bow.Draw();
  //cube.Draw();
  stage.Draw();
  
  glPopMatrix();

  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw(); // 2D描画
}