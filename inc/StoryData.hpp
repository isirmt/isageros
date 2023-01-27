#pragma once
#include <string>
#include <vector>

namespace Story {
struct Conversation {
  std::string left;
  std::string right;
  std::string speaker;
  std::string text;
};

struct Chapter {
  std::string chapterName;
  std::string stageName;
  std::string gotoScene;
  int gameMode;
  std::vector<Conversation> talks;
};
}  // namespace Story