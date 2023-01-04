#pragma once
#include <GL/glut.h>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "ApplicationPreference.hpp"
#include "Camera.hpp"
#include "Color255.hpp"
#include "SceneBase.hpp"

namespace Scene {
class TitleScene : public SceneBase {
 public:
  TitleScene();
  ~TitleScene() {}

  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override {}
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

 private:
  float deg;
  Color255 boxAmbient;
  Obj::Sphere sphere;
  Obj::Cube cube;
  Obj::ObjFile centerCube;

  Obj::ButtonObject button;
};

}  // namespace Scene