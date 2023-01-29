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
                ApplicationPreference::modelFilePath + "char/monster.obj");
    player.SetScale(PosVec(15, 15, 15));
    player.SetShininess(10);
    player.SetRotate(225, PosVec(0, 1, 0));

    enemy = Obj::ObjFile(PosVec(-200.0, 0.0, -200.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0), ApplicationPreference::modelFilePath + "char/formersubLeader.obj");
    enemy.SetScale(PosVec(15, 15, 15));
    enemy.SetShininess(10);
    enemy.SetRotate(45, PosVec(0, 1, 0));
    
    ball = Obj::Sphere(PosVec(400.0, 35.1, 400.0), PosVec(), PosVec());
    ball.SetScale(PosVec(7, 7, 7));
    ball.SetAmbient(Color255(250, 250, 250));
    ball.SetDiffuse(Color255(.3, .3, .3));
    ball.SetSpecular(Color255(0, 0, 0));

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
    layer2D.AddObject(backbutton);

    innerCol = Color255(70, 170, 230);
    startButton = new Obj::Button(PosVec(30, 100), PosVec(50, 50), true, true);
    startButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    startButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    startButton->SetInnerAnimation(.2f);
    layer2D.AddObject(startButton);

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

    text = new Obj::Text(PosVec(100.0, 35.0), PosVec(),"ボタンをクリックして開始：ストーリーノルマ(勝利)");
    text->SetInnerColor(Color255(250, 250, 250));
    layer2D.AddObject(text);

    text_2 = new Obj::Text(PosVec(1000.0, 35.0), PosVec(),"");
    text_2->SetInnerColor(Color255(250, 250, 250));
    layer2D.AddObject(text_2);

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

    srand((unsigned int)time(NULL));
    gameStart = false;
	ruleView = false;
    cameraFlag = true;
    point = 0;
    shootCount = 0;
    watchingCameraDeg = 0.0;
}

void Scene::SoccerScene::Update() {
    layer2D.Collide();

    stage.Update();
    player.Update();
    enemy.Update();
    ball.Update();

    if(watchingCameraDeg <= 500.0 && !gameStart){
        watchingCameraDeg += 3.0;
        if(cameraFlag){
            Camera::SetAsPerspective(
                ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
                30, 1, 99999, PosVec(1700-watchingCameraDeg, 1700, 1700), 
                PosVec(0, 0, 0), PosVec(0, 1, 0));
        }
        else{
            Camera::SetAsPerspective(
                ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
                30, 1, 99999, PosVec(1700, 1700, 1700-watchingCameraDeg), 
                PosVec(0, 0, 0), PosVec(0, 1, 0));
        }

        if(watchingCameraDeg >= 500.0){
            watchingCameraDeg = 0.0;
            Camera::SetAsPerspective(
                ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
                30, 1, 99999, PosVec(1700, 1700, 1700), PosVec(0, 0, 0), PosVec(0, 1, 0));
            cameraFlag = !cameraFlag;
        }
    }

    if(startButton->GetMouseSelected()){
        startButton->SetMouseOff();
        gameStart = true;
        startButton->SetEnabled(false);

        if(shootCount == 0) point = 0;
        ball.SetPosition(PosVec(400.0, 35.1, 400.0));
        text->SetString("どこにシュートを打つ？");
        text_2->SetString("現在の得点 : " + std::to_string(point));

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

		ruleButton->SetEnabled(false);
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

    if(gameStart){
        Camera::SetAsPerspective(
            ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
            30, 1, 9999, PosVec(1700, 1700, 1700), PosVec(0, 0, 0), PosVec(0, 1, 0));

        if(centerButton->GetMouseSelected()){
            threeMouseCondition(false);
            ball.SetVelocity(PosVec(-800.0, 0.0, -800.0));
            text->SetString("Shoot!!");
            KeeperPosition();
        }
        else if(rightButton->GetMouseSelected()){
            threeMouseCondition(false);
            ball.SetVelocity(PosVec(-480.0, 0.0, -800.0));
            text->SetString("Shoot!!");
            KeeperPosition();
        }
        else if(leftButton->GetMouseSelected()){
            threeMouseCondition(false);
            ball.SetVelocity(PosVec(-800.0, 0.0, -480.0));
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
                    text_2->SetString("現在の得点 : " + std::to_string(point));
                }
                else{
                    text->SetString("Saved...");
                    text_2->SetString("現在の得点 : " + std::to_string(point));
                }

				gameStart = false;
                startButton->SetEnabled(true);

                shootCount++;
                if(shootCount >= 5){
                    if(point >= 3){
                        text->SetString("Winner!");
						if(Story::StoryModeManager::GetGameActive()){
							Story::StoryModeManager::SetGameClear(true);
				            Story::StoryModeManager::SavePlusStep();
				            layer2D.DeleteObject(quotaImage);
				            layer2D.AddObject(quotaImage);
				            startButton->SetEnabled(false);
				            ruleButton->SetEnabled(false);
				            quotaImage->ChangeValueWithAnimation(
				                  &quotaImage->GetVectorPointer(VectorType::POS)->x, 30, 3.f);
						}
                    }
                    else{
                        text->SetString("Lose...");
						if(Story::StoryModeManager::GetGameActive()){
							Story::StoryModeManager::SetGameClear(false);
						}
                    }
                    shootCount = 0;
					ruleButton->SetEnabled(true);

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
        if(!Story::StoryModeManager::GetGameActive()){
            SceneManager::ChangeScene(new TitleScene());
        }
        else{
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

void Scene::SoccerScene::RuleMode(){
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

void Scene::SoccerScene::KeeperPosition(){
    ransu = 0 + rand() % 3;
    if(ransu == 0){
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->x, -200, 3.f);
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->z, -200, 3.f);
    }
    else if(ransu == 1){
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->x, -50, 3.f);
        null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->z, -350, 3.f);
    }
    else if(ransu == 2){
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