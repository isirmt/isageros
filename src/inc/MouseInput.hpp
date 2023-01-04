#pragma once
#include <GL/glut.h>

#include "MouseClickType.hpp"
#include "PositionVector.hpp"
#include "PressFrameEnum.hpp"

namespace Input {
class MouseInput {
 public:
  static void UpdateMouseState(int _button, int _state);
  static void SetMousePos(PosVec _pos) { mouse = _pos; }
  static PosVec GetMouse() { return mouse; }
  static PosVec GetMouseWindow() { return mouseWin; }
  static int GetClick(int _button);
  static float GetWheelRot() { return wheelRot; }

 private:
  static void UpdateClick(int* _value, int _andValue);

 private:
  static float wheelRot;

  static PosVec mouse;
  static PosVec mouseWin;

  static MouseClickType mouseClickType;  // struct

  // and 演算により必要なクリックを取り出す
  static int mouseInputs;  // MOUSE_INPUT_LEFT MOUSE_INPUT_RIGHT
                           // MOUSE_INPUT_MIDDLE MOUSE_INPUT_4 MOUSE_INPUT_5
                           // MOUSE_INPUT_6 MOUSE_INPUT_7 MOUSE_INPUT_8
};
}  // namespace Input