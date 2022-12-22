#pragma once

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
};
}  // namespace Scene
