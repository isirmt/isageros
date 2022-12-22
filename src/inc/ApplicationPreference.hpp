#pragma once
#include <string>

#include "Color255.hpp"
#include "PositionVector.hpp"

class ApplicationPreference {
 public:
  static const std::string applicationName;
  static const PosVec windowSize;
  static const Color255 defaultWorldColor;
};
