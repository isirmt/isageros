#pragma once
#include <string>

#include "Color255.hpp"
#include "PositionVector.hpp"

class ApplicationPreference {
 public:
  inline static const std::string applicationName = "Minigames";
  inline static const PosVec windowSize = PosVec(1280, 720);
  inline static const Color255 defaultWorldColor = Color255("#00C1DB");

  inline static constexpr int ObjectBufferLength = 1024;
  inline static constexpr int ObjectNameLength = 256;

  inline static const std::string imgFilePath = "./assets/img/";
  inline static const std::string modelFilePath = "./assets/model/";
  inline static const std::string jsonFilePath = "./assets/json/";
  inline static const std::string savesFilePath = "./saves/";
  inline static const std::string storySavePath = "story/progress.dat";

  inline static const std::string versionName = "v0.8.2b";
};
