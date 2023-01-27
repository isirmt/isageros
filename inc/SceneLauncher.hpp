#pragma once
#include <string>

#include "SceneBase.hpp"
#include "StoryModeManager.hpp"

namespace Scene {
class SceneLauncher {
 public:
  static SceneBase* LaunchSceneFromStory(std::string _sceneName);
};
}  // namespace Scene