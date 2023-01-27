#pragma once
#include <vector>
#include <string>

namespace Story {
struct StoryRoute {
  int from;
  std::vector<int> tos;
  std::vector<std::string> texts;
  std::vector<int> next;
};

}  // namespace Obj