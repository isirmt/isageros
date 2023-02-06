#include "TableTennisScene.hpp"

#include "StoryScene.hpp"
#include "TitleScene.hpp"
#include "GameSelectorScene.hpp"

Scene::TableTennisScene::TableTennisScene() {
  Camera::SetActive(true);
  SceneBase::SetOrthoCameraWindow();
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  null = new Obj::Null();

  worldMap = Obj::ObjFile(PosVec(60, 5., 0.0), PosVec(), PosVec(),
                          ApplicationPreference::modelFilePath + folderName +
                              "tabletennis_stage.obj");
  worldMap.SetScale(PosVec(100, 100, 100));
  worldMap.SetShininess(20);
  worldMap.SetRotate(0, PosVec(0, 1, 0));

  player =
      Obj::ObjFile(PosVec(130, 0, 0.0), PosVec(), PosVec(),
                   ApplicationPreference::modelFilePath + "char/subLeader.obj");
  player.SetScale(PosVec(7, 7, 7));
  player.SetShininess(10);
  player.SetRotate(-90, PosVec(0, 1, 0));

  rPlayer = Obj::ObjFile(
      PosVec(player.GetPosition().x + 10, player.GetPosition().y + 60,
             player.GetPosition().z - 35),
      PosVec(), PosVec(),
      ApplicationPreference::modelFilePath + folderName + "racket.obj");
  rPlayer.SetScale(PosVec(1.5, 1.5, 1.5));
  rPlayer.SetShininess(10);
  rPlayer.SetRotate(-90, PosVec(0, 1, -1.2));

  enemy =
      Obj::ObjFile(PosVec(-130, 0, 0.0), PosVec(), PosVec(),
                   ApplicationPreference::modelFilePath + "char/drunken.obj");
  enemy.SetScale(PosVec(7, 7, 7));
  enemy.SetShininess(10);
  enemy.SetRotate(90, PosVec(0, 1, 0));

  rEnemy = Obj::ObjFile(
      PosVec(enemy.GetPosition().x - 10, enemy.GetPosition().y + 60,
             enemy.GetPosition().z + 40),
      PosVec(), PosVec(),
      ApplicationPreference::modelFilePath + folderName + "racket.obj");
  rEnemy.SetScale(PosVec(1.5, 1.5, 1.5));
  rEnemy.SetShininess(10);
  rEnemy.SetRotate(-90, PosVec(-1.7, 1, -1.2));

  ball = Obj::Sphere(PosVec(0, 120, 0), PosVec(), PosVec());
  ball.SetScale(PosVec(1, 1, 1));
  ball.SetAmbient(Color255(250, 250, 250));
  ball.SetDiffuse(Color255(.3, .3, .3));
  ball.SetSpecular(Color255(0, 0, 0));

  crowd1 =
      Obj::ObjFile(PosVec(20, 0, 230), PosVec(), PosVec(),
                   ApplicationPreference::modelFilePath + "char/Leader.obj");
  crowd1.SetScale(PosVec(7, 7, 7));
  crowd1.SetShininess(10);
  crowd1.SetRotate(-180, PosVec(0, 1, 0));

  Color255 innerCol;
  innerCol = Color255(255, 100, 50);

  // ルール説明画像配置
  Obj::Image* nImage;
  // 必要分追加
  nImage = new Obj::Image(
      ruleImageOffset, ruleImageSize,
      ApplicationPreference::imgFilePath + "minigames/tabletennis/rule1.ppm");
  rulePics.emplace_back(nImage);
  nImage = new Obj::Image(
      ruleImageOffset, ruleImageSize,
      ApplicationPreference::imgFilePath + "minigames/tabletennis/rule3.ppm");
  rulePics.emplace_back(nImage);
  nImage = new Obj::Image(
      ruleImageOffset, ruleImageSize,
      ApplicationPreference::imgFilePath + "minigames/tabletennis/rule2.ppm");
  rulePics.emplace_back(nImage);

  innerCol = Color255("7894DA");
  ruleBack =
      new Obj::Rectangle(PosVec(ruleImageOffset.x - 5, ruleImageOffset.y - 5),
                         PosVec(ruleImageSize.x + 10, ruleImageSize.y + 30));
  ruleBack->SetInnerColor(innerCol);

  ruleText = new Obj::Text(
      PosVec(ruleImageOffset.x + 5.f, ruleImageOffset.y + ruleImageSize.y + 3),
      PosVec(),
      "ルール説明：次へは画像をクリック！・戻る場合は「ルール」ボタン");
  ruleText->SetInnerColor(Color255(250));

  miniuiImage = new Obj::Image(
      PosVec(0, 30), PosVec(75, 190),
      ApplicationPreference::imgFilePath + "minigames/miniui.ppm");

  innerCol = Color255(255, 100, 50);
  backButton = new Obj::Button(PosVec(30, 30), PosVec(50, 50), true, true);
  backButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                            innerCol * 0.75);
  backButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
  backButton->SetInnerAnimation(.2f);

  innerCol = Color255(70, 170, 230);
  startButton = new Obj::Button(PosVec(30, 30 + (50 + 20) * 1), PosVec(50, 50),
                                true, true);
  startButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                             innerCol * 0.75);
  startButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
  startButton->SetInnerAnimation(.2f);

  innerCol = Color255(70, 100, 230);
  ruleButton = new Obj::Button(PosVec(30, 30 + (50 + 20) * 2), PosVec(50, 50),
                               true, true);
  ruleButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                            innerCol * 0.75);
  ruleButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
  ruleButton->SetInnerAnimation(.2f);

  innerCol = Color255("#57B7F3");
  rect = new Obj::Rectangle(PosVec(0, 0), PosVec(50, 50), true, false);
  rect->SetInnerColor(innerCol);

  rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x,
                                 0.f, 10.f);
  rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y,
                                 0.f, 10.f);

  text = new Obj::Text(PosVec(100 + 10, 35), PosVec(),
                       "ボタンをクリックして開始：ストーリーノルマ(" +
                           std::to_string(quotaScore) + ")");
  text->SetInnerColor(Color255(250, 250, 250));

  innerCol = Color255(70, 70, 230);
  textBack = new Obj::Rectangle(
      PosVec(100, 30), PosVec(ApplicationPreference::windowSize.x - 150, 30));
  textBack->SetInnerColor(innerCol);

  goRect = new Obj::Image(
      PosVec(ApplicationPreference::windowSize.x / 2.f, -100), PosVec(0, 0),
      ApplicationPreference::imgFilePath + "minigames/gameover.ppm");

  // no layer add

  innerCol = Color255("#57B7F3");
  quotaImage = new Obj::Image(
      PosVec(-500, 450), PosVec(150, 100),
      ApplicationPreference::imgFilePath + "minigames/quotaAc.ppm");
  // no layer add

  cooldownBox =
      new Obj::Rectangle(PosVec(300, 300), PosVec(20, 150), true, true);
  cooldownBox->SetInnerColor(Color255("D879EA", 0));

  layer2D.AddObject(null);
  layer2D.AddObject(miniuiImage);
  layer2D.AddObject(backButton);
  layer2D.AddObject(startButton);
  layer2D.AddObject(ruleButton);
  layer2D.AddObject(textBack);
  layer2D.AddObject(text);
  layer2D.AddObject(rect);

  Scene::LightManager::Set(
      GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
      Color255(1.f, 1.f, 1.f, 1.0f), Color255(0.0f, 0.0f, 0.0f, 1.f));

  isGameStart = false;
  isPlayerTurn = false;

  playerHitBall = 0;
  waitingCameraDeg = 0;

  isShowingRule = false;

  timer = timerMax;
  turn = 0;

  cooldown = cooldownMax;
}

void Scene::TableTennisScene::Update() {
  layer2D.Collide();

  worldMap.Update();
  player.Update();
  enemy.Update();
  rPlayer.Update();
  rEnemy.Update();
  ball.Update();
  crowd1.Update();

  PosVec cameraPos;
  PosVec cameraLookat;
  PosVec cameraDirection;

  // 外野は常に床と接地判定
  if (crowd1.GetPosition().y < 0) {
    crowd1.SetPosition(
        PosVec(crowd1.GetPosition().x, 0, crowd1.GetPosition().z));
    crowd1.SetVelocity(PosVec());
    crowd1.SetAcceleration(PosVec());
  }

  // ラケットは常に追従
  PosVec rDestination;
  rDestination =
      PosVec(player.GetPosition().x + 10, player.GetPosition().y + 60,
             player.GetPosition().z - 35);
  null->ChangeValueWithAnimation(&rPlayer.GetPositionPointer()->x,
                                 rDestination.x, 3.f);
  null->ChangeValueWithAnimation(&rPlayer.GetPositionPointer()->y,
                                 rDestination.y, 3.f);
  null->ChangeValueWithAnimation(&rPlayer.GetPositionPointer()->z,
                                 rDestination.z, 3.f);

  rDestination = PosVec(enemy.GetPosition().x - 10, enemy.GetPosition().y + 60,
                        enemy.GetPosition().z + 40);
  null->ChangeValueWithAnimation(&rEnemy.GetPositionPointer()->x,
                                 rDestination.x, 3.f);
  null->ChangeValueWithAnimation(&rEnemy.GetPositionPointer()->y,
                                 rDestination.y, 3.f);
  null->ChangeValueWithAnimation(&rEnemy.GetPositionPointer()->z,
                                 rDestination.z, 3.f);

  if (isGameStart) {
    cooldown -= Time::DeltaTime();
    cooldownBox->ChangeValueWithAnimation(
        &cooldownBox->GetVectorPointer(VectorType::SIZE)->y,
        150.f * (cooldown / cooldownMax), .1f);
    cooldownBox->SetInnerColor(Color255("D879EA"));

    if (cooldown <= 0.f) {
      cooldownBox->ChangeValueWithAnimation(
          &cooldownBox->GetVectorPointer(VectorType::SIZE)->y, 150.f, .1f);
      cooldownBox->SetInnerColor(Color255("3AC886"));
      cooldown = 0.f;
    }

    /***************/
    /* UI管理 */
    /***************/

    if (goRect->GetPos().y < -70) layer2D.DeleteObject(goRect);

    /***************/
    /* カメラ設定 */
    /***************/
    cameraPos = PosVec(400, 500, 0);
    cameraLookat = PosVec();
    cameraDirection = PosVec(-1, 0, 0);

    /***************/
    /* 擬似物理演算 */
    /***************/
    if (ball.GetPosition().y < groundLevel && std::fabs(ball.GetPosition().x)) {
      ball.SetVelocity(PosVec(ball.GetVelocity().x,
                              -ball.GetVelocity().y * paramE,
                              ball.GetVelocity().z));
      ball.SetPosition(
          PosVec(ball.GetPosition().x, groundLevel, ball.GetPosition().z));
    }

    if (ball.GetPosition().x < -stageEndAbs.x) {
      ball.SetPosition(
          PosVec((std::signbit(ball.GetPosition().x) ? -1.f : 1.f) *
                     stageEndAbs.x * 0.95f,
                 ball.GetPosition().y, ball.GetPosition().z));
      ball.SetVelocity(PosVec(-ball.GetVelocity().x, ball.GetVelocity().y,
                              ball.GetVelocity().z));
      isPlayerTurn = true;
      null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->z,
                                     ball.GetPosition().z, 3.f);
    }

    if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST &&
        cooldown == 0.f)
      cooldown = cooldownMax;

    // プレイヤーによる跳ね返り
    if (ball.GetPosition().x > canHitXstart &&
        ball.GetPosition().x < canHitXend) {
      // ball.SetAmbient(Color255("#FF9B00"));
      null->ChangeColorWithAnimation(ball.GetAmbientPointer(),
                                     new Color255("#FF9B00"), .1f);
      if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST &&
          isPlayerTurn && cooldown == cooldownMax) {
        ball.SetPosition(
            PosVec((std::signbit(ball.GetPosition().x) ? -1.f : 1.f) *
                       ball.GetPosition().x,
                   ball.GetPosition().y, ball.GetPosition().z));
        ball.SetVelocity(PosVec(-ball.GetVelocity().x, ball.GetVelocity().y,
                                ball.GetVelocity().z));
        isPlayerTurn = false;
        null->ChangeValueWithAnimation(&player.GetPositionPointer()->z,
                                       ball.GetPosition().z, 3.f);
        playerHitBall++;
        text->SetString("ボールを返した回数: " + std::to_string(playerHitBall));

        // 外野を飛ばす

        crowd1.SetVelocity(PosVec(0, 100, 0));
        crowd1.SetAcceleration(PosVec(0, -paramG, 0));
      }
    } else {
      null->ChangeColorWithAnimation(ball.GetAmbientPointer(),
                                     new Color255(250), .1f);
    }

    if (std::fabs(ball.GetPosition().z) > stageEndAbs.z &&
        std::fabs(ball.GetPosition().x) < stageEndAbs.x) {
      ball.SetPosition(
          PosVec(ball.GetPosition().x, ball.GetPosition().y,
                 (std::signbit(ball.GetPosition().z) ? -1.f : 1.f) *
                     stageEndAbs.z * 0.9f));
      // std::cout << std::signbit(ball.GetPosition().z) << std::endl;
      ball.SetVelocity(PosVec(ball.GetVelocity().x, ball.GetVelocity().y,
                              -ball.GetVelocity().z));
    }

    /***************/
    /* 場外処理 */
    /***************/
    if (std::fabs(ball.GetPosition().x) > 200) {
      GameOver();
    }

  } else {
    /* 外野ぴょんぴょん */
    if (crowd1.GetPosition().y == 0.0) {
      crowd1.SetVelocity(PosVec(0, 100, 0));
      crowd1.SetAcceleration(PosVec(0, -paramG, 0));
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

    /***************/
    /* カメラ設定 */
    /***************/
    // cameraPos = PosVec(700, 600, 450);
    cameraDirection = PosVec(0, 1, 0);

    waitingCameraDeg += 2.f * M_PI * .05 * Time::DeltaTime();

    cameraPos =
        PosVec(500 * cosf(waitingCameraDeg), 600, 500 * sinf(waitingCameraDeg));

    timer -= Time::DeltaTime();
    if (timer < 0) {
      timer = timerMax;
      turn++;
      if (turn >= turnMax) turn = 0;
    }
    switch (turn) {
      case 0:
        cameraPos = PosVec(500 * cosf(waitingCameraDeg), 600,
                           500 * sinf(waitingCameraDeg));
        cameraLookat = PosVec();
        break;

      case 1:
        cameraPos =
            PosVec(player.GetPosition().x + 175 * cosf(waitingCameraDeg), 150,
                   175 * sinf(waitingCameraDeg));
        cameraLookat = PosVec(player.GetPosition().x, 55, 0);
        break;
      case 2:
        cameraPos = PosVec(enemy.GetPosition().x + 175 * cosf(waitingCameraDeg),
                           150, 175 * sinf(waitingCameraDeg));
        cameraLookat = PosVec(enemy.GetPosition().x, 55, 0);
        break;

      default:
        break;
    }

    /***************/
    /* ボール演算停止 */
    /***************/
    ball.SetPosition(PosVec(0, 120, 0));
    ball.SetVelocity(PosVec());
    ball.SetAcceleration(PosVec());
  }

  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, cameraPos, cameraLookat, cameraDirection);

  if (backButton->GetMouseSelected()) {
    backButton->SetMouseOff();
    if (!Story::StoryModeManager::GetGameActive())
      SceneManager::ChangeScene(new GameSelectorScene());
    else {
      Story::StoryModeManager::SetGameActive(false);
      SceneManager::ChangeScene(new StoryScene());
    }
    return;
  }

  if (ruleButton->GetMouseSelected()) {
    ruleButton->SetMouseOff();
    isShowingRule = !isShowingRule;
    SetupCurrentRuleDisplayingMode();
  }
  if (startButton->GetMouseSelected()) {
    startButton->SetMouseOff();
    GameStart();
  }

  if (isShowingRule) {
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

void Scene::TableTennisScene::SetupCurrentRuleDisplayingMode() {
  if (!isShowingRule) {
    for (auto& item : rulePics) {
      layer2D.DeleteObject(item);
    }
    layer2D.DeleteObject(ruleBack);
    layer2D.DeleteObject(ruleText);
  } else {
    if (rulePics.size() != 0) {
      layer2D.AddObject(ruleBack);
      layer2D.AddObject(ruleText);
      layer2D.AddObject(rulePics[0]);
    } else
      isShowingRule = false;
  }
}

void Scene::TableTennisScene::GameStart() {
  isGameStart = true;
  ball.SetPosition(PosVec(0, 120, 0));
  std::random_device rnd;
  PosVec fv = PosVec(-1.f * (((int)(rnd()) % 100) + 275), 0,
                     ((int)(rnd()) % 425) - 450);
  ball.SetVelocity(fv);
  ball.SetAcceleration(PosVec(0, -paramG, 0));
  playerHitBall = 0;

  isShowingRule = false;
  SetupCurrentRuleDisplayingMode();

  startButton->SetEnabled(false);
  ruleButton->SetEnabled(false);

  goRect->ChangeValueWithAnimation(
      &goRect->GetVectorPointer(VectorType::SIZE)->x, 1, .3f);
  goRect->ChangeValueWithAnimation(
      &goRect->GetVectorPointer(VectorType::SIZE)->y, 1, .3f);
  goRect->ChangeValueWithAnimation(
      &goRect->GetVectorPointer(VectorType::POS)->x,
      ApplicationPreference::windowSize.x / 2.f, .3f);
  goRect->ChangeValueWithAnimation(
      &goRect->GetVectorPointer(VectorType::POS)->y, -100.f, .3f);
  cooldown = 0.f;

  layer2D.AddObject(cooldownBox);

  // cooldownBox->ChangeValueWithAnimation(&cooldownBox->GetColor(ColorType::INNER)->a,
  // 1.f, 2.f);
}

void Scene::TableTennisScene::GameOver() {
  isGameStart = false;

  startButton->SetEnabled(true);
  ruleButton->SetEnabled(true);

  if (playerHitBall >= quotaScore && Story::StoryModeManager::GetGameActive()) {
    Story::StoryModeManager::SetGameClear(true);
    Story::StoryModeManager::SavePlusStep();
    layer2D.DeleteObject(quotaImage);
    layer2D.AddObject(quotaImage);
    startButton->SetEnabled(false);
    ruleButton->SetEnabled(false);
    quotaImage->ChangeValueWithAnimation(
        &quotaImage->GetVectorPointer(VectorType::POS)->x, 30, 3.f);
  } else if (Story::StoryModeManager::GetGameActive()) {
    Story::StoryModeManager::SetGameClear(false);
  }

  layer2D.DeleteObject(cooldownBox);

  // cooldownBox->ChangeValueWithAnimation(&cooldownBox->GetColor(ColorType::INNER)->a,
  // 0.f, 2.f);

  timer = timerMax;
  goTimer = goTimerMax;

  turn = 0;

  null->ChangeValueWithAnimation(&player.GetPositionPointer()->z, 0.f, 8.f);
  null->ChangeValueWithAnimation(&enemy.GetPositionPointer()->z, 0.f, 8.f);

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

void Scene::TableTennisScene::Draw() {
  SceneBase::Set3DDrawMode();
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  glPushMatrix();  // 3D描画
  worldMap.Draw();
  player.Draw();
  enemy.Draw();
  rPlayer.Draw();
  rEnemy.Draw();
  ball.Draw();
  crowd1.Draw();
  glPopMatrix();

  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}

void Scene::TableTennisScene::MouseProc(int button, int state, int x, int y) {}
