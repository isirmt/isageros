#include "StoryModeManager.hpp"

bool Story::StoryModeManager::isActive = false;
bool Story::StoryModeManager::isGameClear = false;
int Story::StoryModeManager::gameModeNum = 0;
std::string  Story::StoryModeManager::storyProgressFilePath = "story/progress.dat";