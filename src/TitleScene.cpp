#include "TitleScene.hpp"

#include "TableTennisScene.hpp"
#include "StoryScene.hpp"
#include "SumoScene.hpp"
#include "GameSelectorScene.hpp"

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

  modeButton =
      new Obj::Button(Obj::Object2DAnchor::AnchorLowerRight(PosVec(
                          menuButtonOffset.x + menuButtonSize.x,
                          menuButtonOffset.y +
                              (menuButtonSize.y + menuButtonGap.y) * countNum)),
                      menuButtonSize, true, true);
  modeButton->SetInnerColor(buttonInnerColor, buttonInnerColor / 1.2,
                              buttonInnerColor / 1.7, buttonInnerColor / 1.4);
  modeButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  modeButton->SetInnerAnimation(.2f);

  countNum++;
  sumoButton =
      new Obj::Button(Obj::Object2DAnchor::AnchorLowerRight(PosVec(
                          menuButtonOffset.x + menuButtonSize.x,
                          menuButtonOffset.y +
                              (menuButtonSize.y + menuButtonGap.y) * countNum)),
                      menuButtonSize, true, true);
  sumoButton->SetInnerColor(buttonInnerColor, buttonInnerColor / 1.2,
                               buttonInnerColor / 1.7, buttonInnerColor / 1.4);
  sumoButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  sumoButton->SetInnerAnimation(.2f);

  countNum++;
  storyButton =
      new Obj::Button(Obj::Object2DAnchor::AnchorLowerRight(PosVec(
                          menuButtonOffset.x + menuButtonSize.x,
                          menuButtonOffset.y +
                              (menuButtonSize.y + menuButtonGap.y) * countNum)),
                      menuButtonSize, true, true);
  storyButton->SetInnerColor(buttonInnerColor, buttonInnerColor / 1.2,
                               buttonInnerColor / 1.7, buttonInnerColor / 1.4);
  storyButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  storyButton->SetInnerAnimation(.2f);

  metaText = new Obj::Text(PosVec(), PosVec(), "Test Mode");
  metaText->SetInnerColor(Color255(0, 0, 0));

  LightManager::Set(GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
                    Color255(1.f, 1.f, 1.f, 1.0f),
                    Color255(0.0f, 0.0f, 0.0f, 1.f));

  layer2D.AddObject(background);
  layer2D.AddObject(modeButton);
  layer2D.AddObject(sumoButton);
  layer2D.AddObject(storyButton);
  layer2D.AddObject(metaText);
}

void Scene::TitleScene::Update() {
  layer2D.Collide();

  if (modeButton->GetMouseSelected()) {
    modeButton->SetMouseOff();
    SceneManager::ChangeScene(new GameSelectorScene());
    return;
  }

  if (sumoButton->GetMouseSelected()) {
    sumoButton->SetMouseOff();
    SceneManager::ChangeScene(new SumoScene());
    return;
  }

  if (storyButton->GetMouseSelected()) {
    storyButton->SetMouseOff();
    SceneManager::ChangeScene(new StoryScene());
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