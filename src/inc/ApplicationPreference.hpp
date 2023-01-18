#pragma once
#include <string>

#include "Color255.hpp"
#include "PositionVector.hpp"

class ApplicationPreference {
 public:
  static const std::string applicationName;
  static const PosVec windowSize;
  static const Color255 defaultWorldColor;

  static constexpr int ObjectBufferLength = 1024;
  static constexpr int ObjectNameLength = 256;

  static const std::string imgFilePath;
  static const std::string modelFilePath;
};
