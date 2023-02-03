#include "SumoScene.hpp"
#include "TitleScene.hpp"
#include "StoryScene.hpp"

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

    miniuiImage = new Obj::Image(
        PosVec(0, 30), PosVec(75, 190),
        ApplicationPreference::imgFilePath + "minigames/miniui.ppm");
    layer2D.AddObject(miniuiImage);

    Color255 innerCol;
    innerCol = Color255(255, 100, 50);
    backbutton = new Obj::Button(PosVec(30, 30), PosVec(50, 50), true, true);
    backbutton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backbutton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backbutton->SetInnerAnimation(.2f);

    innerCol = Color255(70, 170, 230);
    startbutton = new Obj::Button(PosVec(30, 100), PosVec(50, 50), true, true);
    startbutton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    startbutton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    startbutton->SetInnerAnimation(.2f);

    layer2D.AddObject(backbutton);
    layer2D.AddObject(startbutton);

    gamestart = false;
    ruleView = false;
    flag = false;
    cameraFlag = true;
    cameraFlag_2 = true;

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
                "ボタンをクリックして開始：ストーリーノルマ(勝利)");
    text->SetInnerColor(Color255(250.0, 250.0, 250.0));
    layer2D.AddObject(text);

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

    watchingCameraDeg = 0.0;
}

void Scene::SumoScene::Update(){
    layer2D.Collide();

    stage.Update();
    player.Update();
    enemy.Update();

    if(watchingCameraDeg <= 500.0 && !gamestart){
        watchingCameraDeg += 5.0;
        if(cameraFlag && cameraFlag_2){
            Camera::SetAsPerspective(
                ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
                30, 1, 99999, PosVec(1000+watchingCameraDeg, 1000, 1000), 
                PosVec(0, 0, 0), PosVec(0, 1, 0));
            if(watchingCameraDeg > 500.0){
                watchingCameraDeg = 0.0;
                cameraFlag_2 = !cameraFlag_2;
            }
        }
        else if(cameraFlag && !cameraFlag_2){
            Camera::SetAsPerspective(
                ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
                30, 1, 99999, PosVec(1500-watchingCameraDeg, 1000, 1000), 
                PosVec(0, 0, 0), PosVec(0, 1, 0));
            if(watchingCameraDeg > 500.0){
                watchingCameraDeg = 0.0;
                cameraFlag = !cameraFlag;
                cameraFlag_2 = !cameraFlag_2;
            }
        }
        else if(!cameraFlag && cameraFlag_2){
            Camera::SetAsPerspective(
                ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
                30, 1, 99999, PosVec(1000, 1000, 1000+watchingCameraDeg), 
                PosVec(0, 0, 0), PosVec(0, 1, 0));
            if(watchingCameraDeg > 500.0){
                watchingCameraDeg = 0.0;
                cameraFlag_2 = !cameraFlag_2;
            }
        }
        else if(!cameraFlag && !cameraFlag_2){
            Camera::SetAsPerspective(
                ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
                30, 1, 99999, PosVec(1000, 1000, 1500-watchingCameraDeg), 
                PosVec(0, 0, 0), PosVec(0, 1, 0));
            if(watchingCameraDeg > 500.0){
                watchingCameraDeg = 0.0;
                cameraFlag = !cameraFlag;
                cameraFlag_2 = !cameraFlag_2;
            }
        }
    }

    if(Story::StoryModeManager::GetGameModeNum() == 1 && !gamestart){
        player = Obj::ObjFile(PosVec(470, 106.0, -70.0), PosVec(), PosVec(), 
                    ApplicationPreference::modelFilePath + "char/subLeader.obj");
        player.SetScale(PosVec(10, 10, 10));
        player.SetShininess(10);
        player.SetRotate(-45, PosVec(0, 1, 0));

        enemy = Obj::ObjFile(PosVec(-10.0, 105.0, 410.0), PosVec(), PosVec(), 
                    ApplicationPreference::modelFilePath + "char/formerLeader.obj");
        enemy.SetScale(PosVec(10, 10, 10));
        enemy.SetShininess(10);
        enemy.SetRotate(-225, PosVec(0, 1, 0));
    }
    else if(Story::StoryModeManager::GetGameModeNum() == 0 && !gamestart){
        player = Obj::ObjFile(PosVec(470, 106.0, -70.0), PosVec(), PosVec(), 
                    ApplicationPreference::modelFilePath + "char/formerLeader.obj");
        player.SetScale(PosVec(10, 10, 10));
        player.SetShininess(10);
        player.SetRotate(-45, PosVec(0, 1, 0));

        enemy = Obj::ObjFile(PosVec(-10.0, 105.0, 410.0), PosVec(), PosVec(), 
                    ApplicationPreference::modelFilePath + "char/subLeader.obj");
        enemy.SetScale(PosVec(10, 10, 10));
        enemy.SetShininess(10);
        enemy.SetRotate(-225, PosVec(0, 1, 0));
    }

    if(startbutton->GetMouseSelected()){ 
        startbutton->SetMouseOff();
        gamestart = true;
        pushPower = 0.0;
        clickCount = 0;
        startbutton->SetEnabled(false);
        ruleButton->SetEnabled(false);
        text->SetString("Fight!!");

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

    if(gamestart){
        if (goRect->GetPos().y < -70) layer2D.DeleteObject(goRect);

        Camera::SetAsPerspective(
            ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
            30, 1, 99999, PosVec(1000, 1000, 1000), PosVec(0, 0, 0), PosVec(0, 1, 0));

        if(player.GetPosition().y > 105.0){
            player.SetPosition(PosVec(220, 105.0, 90.0));
            player.SetVelocity(PosVec(-100.0, 0.0, 100.0));
            enemy.SetPosition(PosVec(140.0, 105.0, 160.0));
            enemy.SetVelocity(PosVec(100.0, 0.0, -100.0));
        } 
        
        if(player.GetPosition().x < enemy.GetPosition().x + 35.0){
            player.SetVelocity(PosVec(20.0, 0.0, -20.0));
            enemy.SetVelocity(PosVec(20.0, 0.0, -20.0));
            flag = true;
        }

        if(Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST && flag){
            pushPower += 10.0;
            clickCount++;
            player.SetVelocity(PosVec(-pushPower, 0.0, pushPower));
            enemy.SetVelocity(PosVec(-pushPower, 0.0, pushPower));
        }

        if(enemy.GetPosition().x <= 50.0 && enemy.GetPosition().z >= 350.0 || 
            player.GetPosition().x >= 405.0 && player.GetPosition().z <= -5.0){
            gamestart = false;
            flag = false;
            startbutton->SetEnabled(true);
            ruleButton->SetEnabled(true);
            
            if(enemy.GetPosition().x <= 50.0){
                text->SetString("Winner!!!  クリックした回数 : " + std::to_string(clickCount));
                if(Story::StoryModeManager::GetGameActive()){
                    Story::StoryModeManager::SetGameClear(true);
                    Story::StoryModeManager::SavePlusStep();
                    layer2D.DeleteObject(quotaImage);
                    layer2D.AddObject(quotaImage);
                    startbutton->SetEnabled(false);
                    ruleButton->SetEnabled(false);
                    quotaImage->ChangeValueWithAnimation(
                        &quotaImage->GetVectorPointer(VectorType::POS)->x, 30, 3.f);
                }
            }
            if(player.GetPosition().x >= 405.0){
                text->SetString("Lose...    クリックした回数 : " + std::to_string(clickCount));
                if(Story::StoryModeManager::GetGameActive()){
                    Story::StoryModeManager::SetGameClear(false);
                }
            }

            player.SetPosition(PosVec(470, 106.0, -70.0));
            enemy.SetPosition(PosVec(-10.0, 105.0, 410.0));
            player.SetVelocity(PosVec(0.0, 0.0, 0.0));
            enemy.SetVelocity(PosVec(0.0, 0.0, 0.0));

            goTimer = goTimerMax;

            layer2D.DeleteObject(goRect);
            layer2D.AddObject(goRect);

            goRect->ChangeValueWithAnimation(
                &goRect->GetVectorPointer(VectorType::SIZE)->x,
                ApplicationPreference::windowSize.x / 2.f, 5.f);
            goRect->ChangeValueWithAnimation(
                &goRect->GetVectorPointer(VectorType::SIZE)->y,
                ApplicationPreference::windowSize.y / 4.f, 5.f);
            goRect->ChangeValueWithAnimation(
                &goRect->GetVectorPointer(VectorType::POS)->x,
                ApplicationPreference::windowSize.x / 4.f, 5.f);
            goRect->ChangeValueWithAnimation(
                &goRect->GetVectorPointer(VectorType::POS)->y,
                ApplicationPreference::windowSize.y / 4.f, 5.f);
        }
    }

    goTimer -= Time::DeltaTime();
    if (goTimer < 0) {
      goRect->ChangeValueWithAnimation(
          &goRect->GetVectorPointer(VectorType::SIZE)->x, 1, .3f);
      goRect->ChangeValueWithAnimation(
          &goRect->GetVectorPointer(VectorType::SIZE)->y, 1, .3f);
      goRect->ChangeValueWithAnimation(
          &goRect->GetVectorPointer(VectorType::POS)->x,
          ApplicationPreference::windowSize.x / 2.f, .3f);
      goRect->ChangeValueWithAnimation(
          &goRect->GetVectorPointer(VectorType::POS)->y, -100.f, .3f);
      if (goRect->GetPos().y < -70) layer2D.DeleteObject(goRect);
    }

    if (backbutton->GetMouseSelected()) {
        backbutton->SetMouseOff();
        if (!Story::StoryModeManager::GetGameActive())
            SceneManager::ChangeScene(new TitleScene());
        else {
            Story::StoryModeManager::SetGameActive(false);
            SceneManager::ChangeScene(new StoryScene());
        }
        return;
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
}

void Scene::SumoScene::RuleMode(){
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