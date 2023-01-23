#include "SceneLauncher.hpp"

#include "ArcheryScene.hpp"
#include "BattingScene.hpp"
#include "SumoScene.hpp"
#include "TableTennisScene.hpp"
#include "TitleScene.hpp"

Scene::SceneBase* Scene::SceneLauncher::LaunchSceneFromStory(
    std::string _sceneName) {
  SceneBase* res = nullptr;
  if (_sceneName == "tabletennis") {
    res = new TableTennisScene();
    Story::StoryModeManager::SetGameActive(true);
  } else if (_sceneName == "archery") {
    res = new ArcheryScene();
    Story::StoryModeManager::SetGameActive(true);
  } else if (_sceneName == "sumo") {
    res = new SumoScene();
    Story::StoryModeManager::SetGameActive(true);
  } else if (_sceneName == "batting") {
    res = new BattingScene();
    Story::StoryModeManager::SetGameActive(true);
  } else if (_sceneName == "title") {
    res = new TitleScene();
  }
  return res;
}