#include "TitleScene.hpp"

#include "ArcheryScene.hpp"
#include "TableTennisScene.hpp"
#include "BattingScene.hpp"

Scene::TitleScene::TitleScene() {
  Camera::SetActive(true);
  SceneBase::SetOrthoCameraWindow();
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  background = new Obj::Image(
      PosVec(), ApplicationPreference::windowSize,
      ApplicationPreference::imgFilePath + folderName + "titleBack.ppm");

  PosVec menuButtonOffset(50, 50);
  PosVec menuButtonSize(150, 100);
  PosVec menuButtonGap(0, 20);
  Color255 buttonInnerColor("#40C8C0");
  Color255 buttonOutlineColor(35, 57, 40);
  float buttonOutlineWidth = 2.f;
  int countNum = 0;

  tennisButton =
      new Obj::Button(Obj::Object2DAnchor::AnchorLowerRight(PosVec(
                          menuButtonOffset.x + menuButtonSize.x,
                          menuButtonOffset.y +
                              (menuButtonSize.y + menuButtonGap.y) * countNum)),
                      menuButtonSize, true, true);
  tennisButton->SetInnerColor(buttonInnerColor, buttonInnerColor / 1.2,
                              buttonInnerColor / 1.7, buttonInnerColor / 1.4);
  tennisButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  tennisButton->SetInnerAnimation(.2f);

  countNum++;
  archeryButton =
      new Obj::Button(Obj::Object2DAnchor::AnchorLowerRight(PosVec(
                          menuButtonOffset.x + menuButtonSize.x,
                          menuButtonOffset.y +
                              (menuButtonSize.y + menuButtonGap.y) * countNum)),
                      menuButtonSize, true, true);
  archeryButton->SetInnerColor(buttonInnerColor, buttonInnerColor / 1.2,
                               buttonInnerColor / 1.7, buttonInnerColor / 1.4);
  archeryButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  archeryButton->SetInnerAnimation(.2f);

  countNum++;
  battingButton =
      new Obj::Button(Obj::Object2DAnchor::AnchorLowerRight(PosVec(
                          menuButtonOffset.x + menuButtonSize.x,
                          menuButtonOffset.y +
                              (menuButtonSize.y + menuButtonGap.y) * countNum)),
                      menuButtonSize, true, true);
  battingButton->SetInnerColor(buttonInnerColor, buttonInnerColor / 1.2,
                               buttonInnerColor / 1.7, buttonInnerColor / 1.4);
  battingButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  battingButton->SetInnerAnimation(.2f);

  metaText = new Obj::Text(PosVec(), PosVec(), "Test Mode");
  metaText->SetInnerColor(Color255(0, 0, 0));

  LightManager::Set(GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
                    Color255(1.f, 1.f, 1.f, 1.0f),
                    Color255(0.0f, 0.0f, 0.0f, 1.f));

  layer2D.AddObject(background);
  layer2D.AddObject(archeryButton);
  layer2D.AddObject(tennisButton);
  layer2D.AddObject(battingButton);
  layer2D.AddObject(metaText);
}

void Scene::TitleScene::Update() {
  layer2D.Collide();

  if (tennisButton->GetMouseSelected()) {
    tennisButton->SetMouseOff();
    SceneManager::ChangeScene(new TableTennisScene());
    return;
  }

  if (archeryButton->GetMouseSelected()) {
    archeryButton->SetMouseOff();
    SceneManager::ChangeScene(new ArcheryScene());
    return;
  }

  if (battingButton->GetMouseSelected()) {
    battingButton->SetMouseOff();
    SceneManager::ChangeScene(new BattingScene());
    return;
  }

  layer2D.Update();
}

void Scene::TitleScene::Draw() {
  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}