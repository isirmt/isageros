#pragma once
#include "PositionVector.hpp"

struct MapRelative {
  PosVec cameraPos;
  PosVec cameraLookAt;
  PosVec leftPos;
  PosVec rightPos;
  float charScale;
  float leftRotateY;
  float rightRotateY;
};