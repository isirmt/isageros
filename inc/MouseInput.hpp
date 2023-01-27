#pragma once
#include <GL/glut.h>
#include <stdio.h>

#include "MouseClickType.hpp"
#include "PositionVector.hpp"
#include "PressFrameEnum.hpp"

namespace Input {
class MouseInput {
 public:
  static void Update();
  static void UpdateMouseState(int _button, int _state);
  static void SetMousePos(PosVec _pos) { mouse = _pos; }
  static PosVec GetMouse() { return mouse; }
  static PosVec GetMouseWindow() { return mouseWin; }
  static int GetClick(int _button);
  static float GetWheelRot() { return wheelRot; }

 private:
  static void UpdateClick(int* _value, int* _andValue);

 private:
  static float wheelRot;

  static PosVec mouse;
  static PosVec mouseWin;

  static MouseClickType mouseClickType;  // struct
  static MouseClickType mouseFirstQueue;
  ;  // struct
};
}  // namespace Input