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
  button = new Obj::Button(
      Obj::Object2DAnchor::AnchorUpperLeft(PosVec(30, 100 + 50)),
      PosVec(50, 50), true, true);
  button->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                        innerCol * 0.75);
  button->SetOutlineColor(Color255(35, 57, 40), 5.f);
  button->SetInnerAnimation(.2f);

  DataStore<Story::StoryProgress> progressStore(
      ApplicationPreference::savesFilePath + ApplicationPreference::storySavePath);

  storyProgress = progressStore.Read();

  // std::cout << "nowChapter: " << storyProgress.nowChapter << std::endl;

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
  // picojson relative 読込
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

    posVec.x = static_cast<float>(mapJson["leftPosx"].get<double>());
    posVec.y = static_cast<float>(mapJson["leftPosy"].get<double>());
    posVec.z = static_cast<float>(mapJson["leftPosz"].get<double>());
    mapRelative.leftPos = posVec;

    posVec.x = static_cast<float>(mapJson["rightPosx"].get<double>());
    posVec.y = static_cast<float>(mapJson["rightPosy"].get<double>());
    posVec.z = static_cast<float>(mapJson["rightPosz"].get<double>());
    mapRelative.rightPos = posVec;

    mapRelative.charScale =
        static_cast<float>(mapJson["charScale"].get<double>());
    mapRelative.leftRotateY =
        static_cast<float>(mapJson["leftRotatey"].get<double>());
    mapRelative.rightRotateY =
        static_cast<float>(mapJson["rightRotatey"].get<double>());

    mapRelatives.insert({mapJson["name"].get<std::string>(), mapRelative});
  }

  ////////////////////////////////
  // picojson relative 読込
  ////////////////////////////////
  fs.open(ApplicationPreference::jsonFilePath + routesFilePath,
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
  picojson::array routes = obj["routes"].get<picojson::array>();

  for (auto& item : routes) {
    picojson::object& routeJson = item.get<picojson::object>();

    Story::StoryRoute route;
    route.from = static_cast<int>(routeJson["from"].get<double>());

    picojson::array tos = routeJson["branch"].get<picojson::array>();

    for (auto& to : tos) {
      route.tos.emplace_back(
          static_cast<int>(to.get<picojson::object>()["to"].get<double>()));
      route.texts.emplace_back(
          to.get<picojson::object>()["text"].get<std::string>());
      route.next.emplace_back(
          static_cast<int>(to.get<picojson::object>()["next"].get<double>()));
    }

    this->routes.emplace_back(route);
  }

  ////////////////////////////////
  // オブジェクト設定
  ////////////////////////////////
  innerCol = Color255("#0D0923");
  buttonFrame = new Obj::Button(
      PosVec(), PosVec(ApplicationPreference::windowSize.x, 200), true, true);
  buttonFrame->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65,
                             innerCol * 0.75);
  buttonFrame->SetOutlineColor(Color255(230, 230, 230), 2.f);

  innerCol = Color255("#1B3853");
  speakerFrame =
      new Obj::Rectangle(PosVec(40, 175), PosVec(300, 50), true, true);
  speakerFrame->SetInnerColor(innerCol);

  innerCol = Color255("#1B383C");
  chapterFrame = new Obj::Rectangle(
      Obj::Object2DAnchor::AnchorUpperLeft(PosVec(40, 40 + 50)),
      PosVec(300, 50), true, true);
  chapterFrame->SetInnerColor(innerCol);

  storyText = new Obj::Text(PosVec(50, 150), PosVec(), "");
  storyText->SetInnerColor(Color255(255));

  speakerText = new Obj::Text(PosVec(80, 190), PosVec(), "");
  speakerText->SetInnerColor(Color255(255));

  chapterText = new Obj::Text(
      Obj::Object2DAnchor::AnchorUpperLeft(PosVec(80, 40 + 30)), PosVec(), "");
  chapterText->SetInnerColor(Color255(255));

  cameraOffset = 0;
  dcameraOffset = 20;

  ////////////////////////////////
  // 対応チャプター 読込
  ////////////////////////////////

  branchIndex = -1;
  StoreChapter();

  layer2D.AddObject(button);
  layer2D.AddObject(buttonFrame);
  layer2D.AddObject(storyText);
  layer2D.AddObject(speakerFrame);
  layer2D.AddObject(speakerText);
  layer2D.AddObject(chapterFrame);
  layer2D.AddObject(chapterText);
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

  if (buttonFrame->GetMouseSelected()) {
    buttonFrame->SetMouseOff();
    storyIndex++;
    StorySet();
  }

  if (mustEscape) return;

  PosVec cameraPos = mapRelatives[nowChapter->stageName].cameraPos;
  PosVec lookAt = mapRelatives[nowChapter->stageName].cameraLookAt;

  cameraOffset += dcameraOffset * Time::DeltaTime();

  if (std::fabs(cameraOffset) > cameraOffsetMax) {
    cameraOffset =
        (std::signbit(cameraOffset) ? -1.f : 1.f) * cameraOffsetMax * .95f;
    dcameraOffset *= -1.f;
  }

  cameraPos.z += cameraOffset;

  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, cameraPos, lookAt, PosVec(0, 1, 0));

  // 分岐処理
  int cIndex;
  cIndex = 0;
  bool bButtonSelected = false;
  for (auto& item : branchButtons) {
    if (item->GetMouseSelected()) {
      item->SetMouseOff();
      bButtonSelected = true;
      break;
    }

    cIndex++;
  }

  if (bButtonSelected) {
    branchCIndex = cIndex;
    for (auto& item : branchButtons) {
      layer2D.DeleteObject(item);
      delete item;
    }
    branchButtons.clear();

    for (auto& item : branchTexts) {
      layer2D.DeleteObject(item);
      delete item;
    }
    branchTexts.clear();

    storyProgress.nowChapter = routes[branchIndex].tos[cIndex];
    StoreChapter();
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

void Scene::StoryScene::StorySet() {
  if ((size_t)storyIndex < nowChapter->talks.size()) {
    storyText->SetString(nowChapter->talks[storyIndex].text);
    speakerText->SetString(nowChapter->talks[storyIndex].speaker);

    nowLeft = charObjs[nowChapter->talks[storyIndex].left];
    nowLeft->SetPosition(mapRelatives[nowChapter->stageName].leftPos);
    nowLeft->SetScale(PosVec(mapRelatives[nowChapter->stageName].charScale,
                             mapRelatives[nowChapter->stageName].charScale,
                             mapRelatives[nowChapter->stageName].charScale));
    nowLeft->SetRotate(mapRelatives[nowChapter->stageName].leftRotateY,
                       PosVec(0, 1, 0));
    nowRight = charObjs[nowChapter->talks[storyIndex].right];
    nowRight->SetPosition(mapRelatives[nowChapter->stageName].rightPos);
    nowRight->SetScale(PosVec(mapRelatives[nowChapter->stageName].charScale,
                              mapRelatives[nowChapter->stageName].charScale,
                              mapRelatives[nowChapter->stageName].charScale));
    nowRight->SetRotate(mapRelatives[nowChapter->stageName].rightRotateY,
                        PosVec(0, 1, 0));

  } else {
    Story::StoryProgress prevStoryProgress = storyProgress;

    DataStore<Story::StoryProgress> progressStore(
        ApplicationPreference::savesFilePath + ApplicationPreference::storySavePath);

    storyProgress = progressStore.Read();

    // 枝がないかを確認
    bool isHit = false;
    int routeIndex = 0;
    for (auto& item : routes) {
      if (item.from == prevStoryProgress.nowChapter) {
        isHit = true;
        break;
      }
      routeIndex++;
    }
    if (storyProgress.nowChapter == prevStoryProgress.nowChapter)
      branchIndex = routeIndex;

    if (!isHit && storyProgress.nowChapter == prevStoryProgress.nowChapter) {
      if (storyProgress.nowChapter < storyArray.size() - 1) {
        if (nowChapter->gotoScene == "next") {
          storyProgress.nowChapter++;
          StoreChapter();
          progressStore.Write(storyProgress);
        } else {
          SceneManager::ChangeScene(
              SceneLauncher::LaunchSceneFromStory(nowChapter->gotoScene));
          mustEscape = true;
          return;
        }
      } else {
        // タイトルへ戻る
        SceneManager::ChangeScene(SceneLauncher::LaunchSceneFromStory("title"));
        mustEscape = true;
        return;
      }
    } else if (isHit) {
      // 分岐チャプターそのものか
      if (storyProgress.nowChapter == prevStoryProgress.nowChapter) {
        // 行ったことあるリストに追加
        // button setup

        for (auto& item : branchButtons) {
          layer2D.DeleteObject(item);
          delete item;
        }
        branchButtons.clear();
        for (auto& item : branchTexts) {
          layer2D.DeleteObject(item);
          delete item;
        }
        branchTexts.clear();

        int buttonIndex = 0;
        for (auto& item : routes[routeIndex].tos) {
          Color255 innerColor;
          innerColor = Color255("#1B383C");
          Obj::Button* bButton = new Obj::Button(
              Obj::Object2DAnchor::AnchorUpperLeft(
                  PosVec(ApplicationPreference::windowSize.x / 4.f,
                         150 + 30 + 40 * buttonIndex)),
              PosVec(ApplicationPreference::windowSize.x / 2.f, 30));
          bButton->SetInnerColor(innerColor, innerColor * 0.8,
                                 innerColor * 0.65, innerColor * 0.75);
          bButton->SetInnerAnimation(.1f);
          branchButtons.emplace_back(bButton);

          Obj::Text* bText =
              new Obj::Text(Obj::Object2DAnchor::AnchorUpperLeft(PosVec(
                                ApplicationPreference::windowSize.x / 4.f + 15,
                                143 + 30 + 40 * buttonIndex)),
                            PosVec(), routes[routeIndex].texts[buttonIndex]);
          bText->SetInnerColor(Color255(250));
          branchTexts.emplace_back(bText);
          layer2D.AddObject(bButton);
          layer2D.AddObject(bText);
          buttonIndex++;
        }
      }
    } else {
      if (routes[branchIndex].next[branchCIndex] != -1) {
        storyProgress.nowChapter = routes[branchIndex].next[branchCIndex];
        progressStore.Write(storyProgress);
        StoreChapter();
      } else {
        StorySet();
      }
    }
  }
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
  
  if (nowStage != nullptr) delete nowStage;

  nowStage =
      new Obj::ObjFile(PosVec(), PosVec(), PosVec(),
                       ApplicationPreference::modelFilePath + stageFolderName +
                           nowChapter->stageName + ".obj");
  nowStage->SetScale(PosVec(100, 100, 100));
  chapterText->SetString(nowChapter->chapterName);

  PosVec cameraPos = mapRelatives[nowChapter->stageName].cameraPos;
  PosVec lookAt = mapRelatives[nowChapter->stageName].cameraLookAt;

  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, cameraPos, lookAt, PosVec(0, 1, 0));

  std::map<std::string, std::string> charSets;

  for (auto& item : nowChapter->talks) {
    if (charSets.find(item.left) == charSets.end()) {
      charSets.insert({item.left, ApplicationPreference::modelFilePath +
                                      "char/" + item.left + ".obj"});
    }

    if (charSets.find(item.right) == charSets.end()) {
      charSets.insert({item.right, ApplicationPreference::modelFilePath +
                                       "char/" + item.right + ".obj"});
    }
  }

  for (auto& item : charSets) {
    Obj::ObjFile* obj =
        new Obj::ObjFile(PosVec(), PosVec(), PosVec(), item.second);

    obj->SetScale(PosVec(10, 10, 10));
    charObjs.insert({item.first, obj});
  }

  storyIndex = 0;
  StorySet();
  if (mustEscape) return;
}