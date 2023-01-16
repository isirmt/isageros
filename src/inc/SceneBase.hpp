#pragma once
#include "ApplicationPreference.hpp"
#include "Camera.hpp"
#include "ObjectLayer.hpp"

namespace Scene {
class SceneBase {
 public:
  SceneBase() {}
  ~SceneBase() {}

  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual void KeyboardProc(unsigned char key, int x, int y) = 0;
  virtual void MouseProc(int button, int state, int x, int y) = 0;
  virtual void MotionProc(int x, int y) = 0;
  virtual void PassiveMotionProc(int x, int y) = 0;
  virtual void SpecialFuncProc(int key, int x, int y) = 0;

 protected:
  Obj::ObjectLayer layer2D;

  void SetOrthoCameraWindow();
  // カメラ系関数は含まれていない
  void Set3DDrawMode();
  // カメラ系関数は含まれていない
  void Set2DDrawMode();
};
}  // namespace Scene
