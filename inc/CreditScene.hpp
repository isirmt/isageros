#pragma once
#include <GL/glut.h>

#include <cmath>
#include <iostream>

#include "2DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneManager.hpp"
#include "SceneBase.hpp"

namespace Scene {
class CreditScene : public SceneBase {
 public:
  CreditScene();
  ~CreditScene() {
    delete background;
    delete text;
  }

  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override {}
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

 private:
  Obj::Image* background;

  Obj::Text* text;

  const std::string folderName = "credit/";
};

}  // namespace Scene