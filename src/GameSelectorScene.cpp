#include "GameSelectorScene.hpp"

#include "ArcheryScene.hpp"
#include "BattingScene.hpp"
#include "SceneLauncher.hpp"
#include "SumoScene.hpp"
#include "TableTennisScene.hpp"
#include "TitleScene.hpp"

Scene::GameSelectorScene::GameSelectorScene() {
  Camera::SetActive(true);
  SceneBase::SetOrthoCameraWindow();
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  PosVec selButtonOffset(50, 50);
  PosVec selButtonSize(352, 264);  // 4:3
  PosVec selButtonGap(40, 40);
  Color255 buttonInnerColor("#40C8C0");
  Color255 buttonOutlineColor(35, 57, 40);
  float buttonOutlineWidth = 2.f;
  int horizontalCount = 0;
  int verticalCount = 0;

  background = new Obj::Image(
      PosVec(), ApplicationPreference::windowSize,
      ApplicationPreference::imgFilePath + folderName + "forestBack.ppm");

  Obj::Image* iButton;

  Color255 innerCol;
  innerCol = Color255(255, 100, 50);
  button = new Obj::Button(
      Obj::Object2DAnchor::AnchorUpperLeft(PosVec(30, 30 + 50)),
      PosVec(50, 50), true, true);
  button->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                        innerCol * 0.75);
  button->SetOutlineColor(Color255(35, 57, 40), 5.f);
  button->SetInnerAnimation(.2f);

  horizontalCount = 0;
  verticalCount = 0;
  iButton = new Obj::Image(
      PosVec(selButtonOffset.x +
                 (selButtonSize.x + selButtonGap.x) * horizontalCount,
             selButtonOffset.y +
                 (selButtonSize.y + selButtonGap.y) * verticalCount),
      selButtonSize,
      ApplicationPreference::imgFilePath + folderName + "tabletennis.ppm");
  gameThumbs.insert({"tabletennis", iButton});

  horizontalCount = 1;
  verticalCount = 0;
  iButton = new Obj::Image(
      PosVec(selButtonOffset.x +
                 (selButtonSize.x + selButtonGap.x) * horizontalCount,
             selButtonOffset.y +
                 (selButtonSize.y + selButtonGap.y) * verticalCount),
      selButtonSize,
      ApplicationPreference::imgFilePath + folderName + "archery.ppm");
  gameThumbs.insert({"archery", iButton});

  horizontalCount = 2;
  verticalCount = 0;
  iButton = new Obj::Image(
      PosVec(selButtonOffset.x +
                 (selButtonSize.x + selButtonGap.x) * horizontalCount,
             selButtonOffset.y +
                 (selButtonSize.y + selButtonGap.y) * verticalCount),
      selButtonSize,
      ApplicationPreference::imgFilePath + folderName + "batting.ppm");
  gameThumbs.insert({"batting", iButton});

  horizontalCount = 0;
  verticalCount = 1;
  iButton = new Obj::Image(
      PosVec(selButtonOffset.x +
                 (selButtonSize.x + selButtonGap.x) * horizontalCount,
             selButtonOffset.y +
                 (selButtonSize.y + selButtonGap.y) * verticalCount),
      selButtonSize,
      ApplicationPreference::imgFilePath + folderName + "sumo.ppm");
  gameThumbs.insert({"sumo", iButton});

  horizontalCount = 1;
  verticalCount = 1;
  iButton = new Obj::Image(
      PosVec(selButtonOffset.x +
                 (selButtonSize.x + selButtonGap.x) * horizontalCount,
             selButtonOffset.y +
                 (selButtonSize.y + selButtonGap.y) * verticalCount),
      selButtonSize,
      ApplicationPreference::imgFilePath + folderName + "sumo.ppm");
  gameThumbs.insert({"soccer", iButton});

  LightManager::Set(GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
                    Color255(1.f, 1.f, 1.f, 1.0f),
                    Color255(0.0f, 0.0f, 0.0f, 1.f));

  layer2D.AddObject(background);
  layer2D.AddObject(button);
  for (auto& item : gameThumbs) {
    layer2D.AddObject(item.second);
  }
}

void Scene::GameSelectorScene::Update() {
  layer2D.Collide();

  if (button->GetMouseSelected()) {
    button->SetMouseOff();
    SceneManager::ChangeScene(new TitleScene());
    return;
  }
  for (auto& item : gameThumbs) {
    if (item.second->GetMouseSelected()) {
      item.second->SetMouseOff();
      SceneManager::ChangeScene(
          SceneLauncher::LaunchSceneFromStory(item.first));
      Story::StoryModeManager::SetGameActive(false);
      return;
    }
  }

  layer2D.Update();
}

void Scene::GameSelectorScene::Draw() {
  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}