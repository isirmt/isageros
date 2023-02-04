#include "TitleScene.hpp"

#include "GameSelectorScene.hpp"
#include "CreditScene.hpp"
#include "SettingScene.hpp"
#include "StoryScene.hpp"
#include "SumoScene.hpp"
#include "TableTennisScene.hpp"

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

  PosVec menuButtonSize(500, 75);
  Color255 buttonInnerColor("#40C8C0");
  Color255 buttonOutlineColor(35, 57, 40);
  float buttonOutlineWidth = 2.f;
  PosVec bpos;

  bpos = PosVec(75, 30);
  storyButton = new Obj::Image(
      PosVec(75, 30), menuButtonSize,
      ApplicationPreference::imgFilePath + folderName + "story.ppm");
  storyButton->SetTag(std::to_string(bpos.y));

  bpos =
      Obj::Object2DAnchor::AnchorLowerRight(PosVec(75 + menuButtonSize.x, 30));
  modeButton = new Obj::Image(
      bpos, menuButtonSize,
      ApplicationPreference::imgFilePath + folderName + "mini.ppm");
  modeButton->SetTag(std::to_string(bpos.y));

  settingButton = new Obj::Button(
      Obj::Object2DAnchor::AnchorUpperRight(PosVec(30 + 75, 30 + 25)),
      PosVec(75, 25), true, true);
  settingButton->SetInnerColor(buttonInnerColor, buttonInnerColor * 0.7,
                               buttonInnerColor * 0.6, buttonInnerColor * 0.65);
  settingButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  settingButton->SetInnerAnimation(.1f);

  creditButton = new Obj::Button(
      Obj::Object2DAnchor::AnchorUpperRight(PosVec(30 + 75, 30 + 75)),
      PosVec(75, 25), true, true);
  creditButton->SetInnerColor(buttonInnerColor, buttonInnerColor * 0.7,
                               buttonInnerColor * 0.6, buttonInnerColor * 0.65);
  creditButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  creditButton->SetInnerAnimation(.1f);

  metaText = new Obj::Text(PosVec(), PosVec(), ApplicationPreference::versionName);
  metaText->SetInnerColor(Color255(0, 0, 0));

  LightManager::Set(GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
                    Color255(1.f, 1.f, 1.f, 1.0f),
                    Color255(0.0f, 0.0f, 0.0f, 1.f));

  system("vlc /bulid/assets/music/Isageros_Opening.ogg");

  layer2D.AddObject(background);
  layer2D.AddObject(modeButton);
  layer2D.AddObject(storyButton);
  layer2D.AddObject(settingButton);
  layer2D.AddObject(creditButton);
  layer2D.AddObject(metaText);
}

void Scene::TitleScene::Update() {
  layer2D.Collide();

  if (settingButton->GetMouseSelected()) {
    settingButton->SetMouseOff();
    SceneManager::ChangeScene(new SettingScene());
    return;
  }

  if (creditButton->GetMouseSelected()) {
    creditButton->SetMouseOff();
    SceneManager::ChangeScene(new CreditScene());
    return;
  }

  if (modeButton->GetMouseSelected()) {
    modeButton->SetMouseOff();
    SceneManager::ChangeScene(new GameSelectorScene());
    return;
  }

  if (storyButton->GetMouseSelected()) {
    storyButton->SetMouseOff();
    SceneManager::ChangeScene(new StoryScene());
    return;
  }

  if (storyButton->GetMouseHit()) {
    storyButton->ChangeValueWithAnimation(
        &storyButton->GetVectorPointer(VectorType::POS)->y,
        std::stof(storyButton->GetTag()) + 5.f, 1.f);
  } else {
    storyButton->ChangeValueWithAnimation(
        &storyButton->GetVectorPointer(VectorType::POS)->y,
        std::stof(storyButton->GetTag()), 2.f);
  }

  if (modeButton->GetMouseHit()) {
    modeButton->ChangeValueWithAnimation(
        &modeButton->GetVectorPointer(VectorType::POS)->y,
        std::stof(modeButton->GetTag()) + 5.f, 1.f);
  } else {
    modeButton->ChangeValueWithAnimation(
        &modeButton->GetVectorPointer(VectorType::POS)->y,
        std::stof(modeButton->GetTag()), 2.f);
  }

  layer2D.Update();
}

void Scene::TitleScene::Draw() {
  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}