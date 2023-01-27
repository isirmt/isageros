#pragma once
#include "DataStore.hpp"
#include "StoryProgressData.hpp"
#include "ApplicationPreference.hpp"

namespace Story {
class StoryModeManager {
 public:
  static void SetGameActive(bool _active) {
    isActive = _active;
    if (isActive) {
      isGameClear = false;
      gameModeNum = 0;
    }
  }
  static void SetGameClear(bool _active) { isGameClear = _active; }
  static void SetGameModeNum(int _value = 0) { gameModeNum = _value; }
  static bool GetGameActive() { return isActive; }
  static bool GetGameClear() { return isActive; }
  static int GetGameModeNum() { return gameModeNum; }

  static void SavePlusStep() {
    StoryProgress storyProgress;

    DataStore<StoryProgress> progressStore(
        ApplicationPreference::savesFilePath + storyProgressFilePath);

    storyProgress = progressStore.Read();
    storyProgress.nowChapter++;
    progressStore.Write(storyProgress);
  }

 private:
  static bool isActive;
  static bool isGameClear;
  static int gameModeNum;

  static std::string storyProgressFilePath;
};
}  // namespace Story