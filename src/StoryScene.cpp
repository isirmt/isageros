#include "StoryScene.hpp"

#include "TitleScene.hpp"

Scene::StoryScene::StoryScene()
    : nowChapter(nullptr),
      nowStage(nullptr),
      nowLeft(nullptr),
      nowRight(nullptr),
      buttonFrame(nullptr),
      speakerFrame(nullptr),
      speakerText(nullptr),
      storyText(nullptr) {
  Camera::SetActive(true);
  SceneBase::SetOrthoCameraWindow();
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  Color255 innerCol;
  innerCol = Color255(255, 100, 50);
  button = new Obj::Button(PosVec(30, 30), PosVec(150, 100), true, true);
  button->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                        innerCol * 0.75);
  button->SetOutlineColor(Color255(35, 57, 40), 5.f);
  button->SetInnerAnimation(.2f);

  if (mkdir("./saves", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP |
                           S_IROTH | S_IWOTH) == 0) {
    puts("Info: Created Directory \"./saves\"");
  } else {
    perror("mkdir");
  }
  if (mkdir("./saves/story", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP |
                                 S_IROTH | S_IWOTH) == 0) {
    puts("Info: Created Directory \"./saves/story\"");
  } else {
    perror("mkdir");
  }

  DataStore<Story::StoryProgress> progressStore(
      ApplicationPreference::savesFilePath + storyProgressFilePath);

  storyProgress = progressStore.Read();

  std::cout << "nowChapter: " << storyProgress.nowChapter << std::endl;

  // 書き込み方
  // storyProgress.nowChapter++;
  // progressStore.Write(storyProgress);

  std::stringstream ss;
  std::ifstream fs;
  picojson::value val;
  std::string err;
  picojson::object obj;

  ////////////////////////////////
  // picojson conv 読込
  ////////////////////////////////
  fs.open(ApplicationPreference::jsonFilePath + talksFilePath,
          std::ios::binary);

  if (!fs.is_open()) {
    return;
  }

  ss << fs.rdbuf();
  fs.close();

  ss >> val;
  err = picojson::get_last_error();
  if (!err.empty()) {
    std::cerr << err << std::endl;
    return;
  }

  obj = val.get<picojson::object>();  // オブジェクト取得
  storyArray = obj["stories"].get<picojson::array>();

  ////////////////////////////////
  // picojson conv 読込
  ////////////////////////////////
  fs.open(ApplicationPreference::jsonFilePath + relativeStageFilePath,
          std::ios::binary);

  if (!fs.is_open()) {
    return;
  }

  ss << fs.rdbuf();
  fs.close();

  ss >> val;
  err = picojson::get_last_error();
  if (!err.empty()) {
    std::cerr << err << std::endl;
    return;
  }

  obj = val.get<picojson::object>();  // オブジェクト取得
  picojson::array maps = obj["maps"].get<picojson::array>();

  for (auto& item : maps) {
    picojson::object& mapJson = item.get<picojson::object>();

    MapRelative mapRelative;
    PosVec posVec;
    posVec.x = static_cast<float>(mapJson["camerax"].get<double>());
    posVec.y = static_cast<float>(mapJson["cameray"].get<double>());
    posVec.z = static_cast<float>(mapJson["cameraz"].get<double>());
    mapRelative.cameraPos = posVec;

    posVec.x = static_cast<float>(mapJson["lookx"].get<double>());
    posVec.y = static_cast<float>(mapJson["looky"].get<double>());
    posVec.z = static_cast<float>(mapJson["lookz"].get<double>());
    mapRelative.cameraLookAt = posVec;

    mapRelatives.insert({mapJson["name"].get<std::string>(), mapRelative});
  }

  ////////////////////////////////
  // 対応チャプター 読込
  ////////////////////////////////
  StoreChapter();

  layer2D.AddObject(button);
}

void Scene::StoryScene::Update() {
  layer2D.Collide();

  if (nowStage != nullptr) nowStage->Update();
  if (nowLeft != nullptr) nowLeft->Update();
  if (nowRight != nullptr) nowRight->Update();

  if (button->GetMouseSelected()) {
    button->SetMouseOff();
    SceneManager::ChangeScene(new TitleScene());
    return;
  }

  layer2D.Update();
}

void Scene::StoryScene::Draw() {
  SceneBase::Set3DDrawMode();
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  glPushMatrix();  // 3D描画
  if (nowStage != nullptr) nowStage->Draw();
  if (nowLeft != nullptr) nowLeft->Draw();
  if (nowRight != nullptr) nowRight->Draw();
  glPopMatrix();

  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}

void Scene::StoryScene::StoreChapter() {
  if (nowChapter != nullptr) delete (nowChapter);
  nowChapter = new Story::Chapter;
  picojson::object& chapterJson =
      storyArray[storyProgress.nowChapter].get<picojson::object>();

  nowChapter->chapterName = chapterJson["chapterName"].get<std::string>();
  nowChapter->stageName = chapterJson["stageName"].get<std::string>();
  nowChapter->gotoScene = chapterJson["goto"].get<std::string>();

  for (auto& item : chapterJson["talks"].get<picojson::array>()) {
    picojson::object& convJson = item.get<picojson::object>();

    Story::Conversation conv;
    conv.left = convJson["left"].get<std::string>();
    conv.right = convJson["right"].get<std::string>();
    conv.speaker = convJson["speaker"].get<std::string>();
    conv.text = convJson["text"].get<std::string>();

    nowChapter->talks.emplace_back(conv);
  }

  std::cout << "nowChapterName: " << nowChapter->chapterName.c_str()
            << std::endl;
  std::cout << "nowStageName: " << nowChapter->stageName.c_str() << std::endl;
  std::cout << "nowGotoScene: " << nowChapter->gotoScene.c_str() << std::endl;

  for (auto& item : nowChapter->talks) std::cout << item.text << std::endl;

  if (nowStage != nullptr) delete nowStage;

  nowStage =
      new Obj::ObjFile(PosVec(), PosVec(), PosVec(),
                       ApplicationPreference::modelFilePath + stageFolderName +
                           nowChapter->stageName + ".obj");
  nowStage->SetScale(PosVec(100, 100, 100));

  PosVec cameraPos = mapRelatives[nowChapter->stageName].cameraPos;
  PosVec lookAt = mapRelatives[nowChapter->stageName].cameraLookAt;

  std::cout << nowChapter->stageName << std::endl;
  std::cout << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << ","
            << std::endl;
  std::cout << lookAt.x << "," << lookAt.y << "," << lookAt.z << ","
            << std::endl;

  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, cameraPos, lookAt, PosVec(0, 1, 0));
}