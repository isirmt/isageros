#include "SettingScene.hpp"

#include "TitleScene.hpp"

Scene::SettingScene::SettingScene() {
  Camera::SetActive(true);
  SceneBase::SetOrthoCameraWindow();
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  background = new Obj::Image(
      PosVec(), ApplicationPreference::windowSize,
      ApplicationPreference::imgFilePath + selectFolderName + "forestBack.ppm");

  PosVec settingButtonOffset(125, 125);
  PosVec settingButtonSize(200, 50);
  PosVec settingButtonGap(30, 30);
  Color255 buttonInnerColor("#40C8C0");
  Color255 buttonOutlineColor(35, 57, 40);
  float buttonOutlineWidth = 2.f;
  int vCount = 0;
  PosVec newPos;

  newPos =
      settingButtonOffset + (settingButtonSize + settingButtonGap) * vCount;
  saveStoryResetButton = new Obj::Button(newPos, settingButtonSize, true, true);
  saveStoryResetButton->SetTag(std::to_string(newPos.y));
  saveStoryResetButton->SetInnerColor(buttonInnerColor, buttonInnerColor * .7f,
                                      buttonInnerColor * .6f,
                                      buttonInnerColor * .65f);
  saveStoryResetButton->SetOutlineColor(buttonOutlineColor, buttonOutlineWidth);
  saveStoryResetButton->SetInnerAnimation(.2f);

  saveStoryResetText = new Obj::Text(PosVec(newPos.x + 5, newPos.y + 17),
                                     PosVec(), "セーブデータリセット");
  saveStoryResetText->SetInnerColor(Color255(20));

  buttonInnerColor = Color255(255, 100, 50);
  backButton = new Obj::Button(PosVec(30, 30), PosVec(50, 50), true, true);
  backButton->SetInnerColor(buttonInnerColor, buttonInnerColor * 0.8,
                            buttonInnerColor * 0.65, buttonInnerColor * 0.75);
  backButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
  backButton->SetInnerAnimation(.2f);

  LightManager::Set(GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
                    Color255(1.f, 1.f, 1.f, 1.0f),
                    Color255(0.0f, 0.0f, 0.0f, 1.f));

  layer2D.AddObject(background);
  layer2D.AddObject(saveStoryResetButton);
  layer2D.AddObject(saveStoryResetText);
  layer2D.AddObject(backButton);
}

void Scene::SettingScene::Update() {
  layer2D.Collide();

  if (saveStoryResetButton->GetMouseSelected()) {
    saveStoryResetButton->SetMouseOff();
    saveStoryResetButton->SetEnabled(false);

    FILE* fp;
    std::string filepath = ApplicationPreference::savesFilePath +
                           ApplicationPreference::storySavePath;
    fp = fopen(filepath.c_str(), "r");

    if (fp != NULL) {
      fclose(fp);
      remove(filepath.c_str());
    }
  }

  if (backButton->GetMouseSelected()) {
    backButton->SetMouseOff();
    SceneManager::ChangeScene(new TitleScene());
    return;
  }

  layer2D.Update();
}

void Scene::SettingScene::Draw() {
  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}