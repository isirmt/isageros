#include "StoryScene.hpp"

Scene::StoryScene::StoryScene() : nowChapter(nullptr) {
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

  DataStore<Story::StoryProgress> progressStore(storyProgressFilePath);

  storyProgress = progressStore.Read();

  std::cout << "nowChapter: " << storyProgress.nowChapter << std::endl;

  // 書き込み方
  // storyProgress.nowChapter++;
  // progressStore.Write(storyProgress);

  ////////////////////////////////
  // picojson 読込
  ////////////////////////////////
  std::stringstream ss;
  std::ifstream fs;
  fs.open(talksFilePath, std::ios::binary);

  if (!fs.is_open()) {
    return;
  }

  ss << fs.rdbuf();
  fs.close();

  picojson::value val;
  ss >> val;
  std::string err = picojson::get_last_error();
  if (!err.empty()) {
    std::cerr << err << std::endl;
    return;
  }

  picojson::object& obj = val.get<picojson::object>();  // オブジェクト取得
  storyArray = obj["stories"].get<picojson::array>();

  ////////////////////////////////
  // 対応チャプター 読込
  ////////////////////////////////
  StoreChapter();

  std::cout << "nowChapterName: " << nowChapter->chapterName.c_str()
            << std::endl;
}

void Scene::StoryScene::Update() {}

void Scene::StoryScene::Draw() {}

void Scene::StoryScene::StoreChapter() {
  if (nowChapter != nullptr) delete (nowChapter);
  nowChapter = new Story::Chapter;

  nowChapter->chapterName = storyArray[storyProgress.nowChapter]
                                .get<picojson::object>()["chapterName"]
                                .get<std::string>();
}