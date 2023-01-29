#pragma once
#include "AnimationStatus.hpp"

struct AnimationColorPointer {
  AnimationColorStatus animation;
  Color255* color;

  inline AnimationColorPointer() : animation(), color(nullptr) {}

  inline AnimationColorPointer(AnimationColorStatus _status, Color255* _color)
      : animation(_status), color(_color) {}
};

struct AnimationPointer {
  AnimationStatus animation;
  float* value;

  inline AnimationPointer() : animation(), value(nullptr) {}

  inline AnimationPointer(AnimationStatus _status, float* _value)
      : animation(_status), value(_value) {}
};

struct AnimationPointerInt {
  AnimationStatus animation;
  int* value;

  inline AnimationPointerInt() : animation(), value(nullptr) {}

  inline AnimationPointerInt(AnimationStatus _status, int* _value)
      : animation(_status), value(_value) {}
};