#include "ApplicationBuilder.hpp"

void GLSYS::ApplicationBuilder::Initialize() {
  Time::Initialize();
  std::setlocale(LC_ALL, "");
}

void GLSYS::ApplicationBuilder::Update() {
  Time::Update();
  Input::MouseInput::Update();
}