#pragma once
#include <array>

#include "Color255.hpp"

struct AnimationColorStatus {
  bool animationEnabled;
  Color255 start;
  Color255 end;
  Color255 current;
  std::array<float, 3> m;
  float duration;
  float durationRemain;
  float elapsedTime;
  float currentlyRate;

  AnimationColorStatus()
      : animationEnabled(false),
        current(0),
        m({}),
        duration(0.f),
        durationRemain(0.f),
        elapsedTime(0.f),
        currentlyRate(0.f),
        start(0),
        end(0) {}
};

struct AnimationStatus {
  bool animationEnabled;
  float start;
  float end;
  float current;
  float m;
  float duration;
  float durationRemain;
  float elapsedTime;
  float currentlyRate;

  AnimationStatus()
      : animationEnabled(false),
        current(0.f),
        m(0.f),
        duration(0.f),
        durationRemain(0.f),
        elapsedTime(0.f),
        currentlyRate(0.f),
        start(0.f),
        end(0.f) {}
};