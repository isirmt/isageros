#include "TableTennisScene.hpp"

#include "TitleScene.hpp"

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
                   ApplicationPreference::modelFilePath + "char/chara.obj");
  player.SetScale(PosVec(5, 5, 5));
  player.SetShininess(10);
  player.SetRotate(90, PosVec(0, 1, 0));

  enemy = Obj::ObjFile(PosVec(-130, 0, 0.0), PosVec(), PosVec(),
                       ApplicationPreference::modelFilePath + "char/chara.obj");
  enemy.SetScale(PosVec(5, 5, 5));
  enemy.SetShininess(10);
  enemy.SetRotate(-90, PosVec(0, 1, 0));

  ball = Obj::Sphere(PosVec(0, 120, 0), PosVec(), PosVec());
  ball.SetScale(PosVec(1, 1, 1));
  ball.SetAmbient(Color255(250, 250, 250));
  ball.SetDiffuse(Color255(.3, .3, .3));
  ball.SetSpecular(Color255(0, 0, 0));

  Color255 innerCol;
  innerCol = Color255(255, 100, 50);
  button = new Obj::Button(PosVec(30, 30), PosVec(150, 100), true, true);
  button->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                        innerCol * 0.75);
  button->SetOutlineColor(Color255(35, 57, 40), 5.f);
  button->SetInnerAnimation(.2f);

  innerCol = Color255(70, 170, 230);
  startButton =
      new Obj::Button(PosVec(30, 30 + 120), PosVec(150, 100), true, true);
  startButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                             innerCol * 0.75);
  startButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
  startButton->SetInnerAnimation(.2f);

  innerCol = Color255("#57B7F3");
  rect = new Obj::Rectangle(PosVec(0, 0), PosVec(50, 50), true, false);
  rect->SetInnerColor(innerCol);

  rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x,
                                 0.f, 10.f);
  rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y,
                                 0.f, 10.f);

  text = new Obj::Text(PosVec(10, 600), PosVec(),
                       "テーブルテニス 卓球 Table_Tennis\nサンプルテキスト");
  text->SetInnerColor(Color255(250, 250, 250));

  image = new Obj::Image(
      Obj::Object2DAnchor::AnchorLowerRight(PosVec(50 + 300, 50)),
      PosVec(300, 150),
      ApplicationPreference::imgFilePath + folderName + "sample.ppm");
  image->SetEnabled(false);

  layer2D.AddObject(null);
  layer2D.AddObject(button);
  layer2D.AddObject(startButton);
  layer2D.AddObject(text);
  layer2D.AddObject(rect);

  Scene::LightManager::Set(
      GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
      Color255(1.f, 1.f, 1.f, 1.0f), Color255(0.0f, 0.0f, 0.0f, 1.f));

  isGameStart = false;
  isPlayerTurn = false;

  playerHitBall = 0;
  waitingCameraDeg = 0;
}

void Scene::TableTennisScene::Update() {
  layer2D.Collide();

  worldMap.Update();
  player.Update();
  enemy.Update();
  ball.Update();

  PosVec cameraPos;
  PosVec cameraDirection;

  if (isGameStart) {
    /***************/
    /* カメラ設定 */
    /***************/
    cameraPos = PosVec(400, 400, 0);
    cameraDirection = PosVec(-1, 0, 0);

    /***************/
    /* 擬似物理演算 */
    /***************/
    if (ball.GetPosition().y < groundLevel) {
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

    // プレイヤーによる跳ね返り
    if (ball.GetPosition().x > canHitXstart &&
        ball.GetPosition().x < canHitXend) {
      if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST &&
          isPlayerTurn) {
        ball.SetPosition(
            PosVec((std::signbit(ball.GetPosition().x) ? -1.f : 1.f) *
                       stageEndAbs.x * 0.95f,
                   ball.GetPosition().y, ball.GetPosition().z));
        ball.SetVelocity(PosVec(-ball.GetVelocity().x, ball.GetVelocity().y,
                                ball.GetVelocity().z));
        isPlayerTurn = false;
        null->ChangeValueWithAnimation(&player.GetPositionPointer()->z,
                                       ball.GetPosition().z, 3.f);
        playerHitBall++;
        text->SetString("playerHitBall: " + std::to_string(playerHitBall));
      }
    }

    if (std::fabs(ball.GetPosition().z) > stageEndAbs.z) {
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
    /***************/
    /* カメラ設定 */
    /***************/
    // cameraPos = PosVec(700, 600, 450);
    cameraDirection = PosVec(0, 1, 0);

    waitingCameraDeg += 2.f * M_PI * .2 * Time::DeltaTime();

    cameraPos =
        PosVec(500 * cosf(waitingCameraDeg), 600, 500 * sinf(waitingCameraDeg));

    /***************/
    /* ボール演算停止 */
    /***************/
    ball.SetPosition(PosVec(0, 120, 0));
    ball.SetVelocity(PosVec());
    ball.SetAcceleration(PosVec());
  }

  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, cameraPos, PosVec(0, 0, 0), cameraDirection);

  if (button->GetMouseSelected()) {
    button->SetMouseOff();
    SceneManager::ChangeScene(new TitleScene());
    return;
  }

  if (startButton->GetMouseSelected()) {
    startButton->SetMouseOff();
    GameStart();
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

void Scene::TableTennisScene::GameStart() {
  isGameStart = true;
  ball.SetPosition(PosVec(0, 120, 0));
  ball.SetVelocity(PosVec(-350, 0, 350));
  ball.SetAcceleration(PosVec(0, -paramG, 0));
  playerHitBall = 0;

  layer2D.AddObject(image);
  startButton->SetEnabled(false);
}

void Scene::TableTennisScene::GameOver() {
  isGameStart = false;
  text->SetString("playerHitBall: " + std::to_string(playerHitBall) +
                  " (GAME OVER)");

  layer2D.DeleteObject(image);
  startButton->SetEnabled(true);
}

void Scene::TableTennisScene::Draw() {
  SceneBase::Set3DDrawMode();
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  glPushMatrix();  // 3D描画
  worldMap.Draw();
  player.Draw();
  enemy.Draw();
  ball.Draw();
  glPopMatrix();

  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}

void Scene::TableTennisScene::MouseProc(int button, int state, int x, int y) {}