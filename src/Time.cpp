#include "Time.hpp"

std::chrono::system_clock::time_point Time::previousTime =
    std::chrono::system_clock::time_point();
double Time::deltaTime = 0.;

void Time::Initialize() { previousTime = std::chrono::system_clock::now(); }

void Time::Update() {
  auto nowTime = std::chrono::system_clock::now();
  deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                  nowTime - previousTime)
                  .count() / 1000.;
  previousTime = nowTime;
}