#include "MouseInput.hpp"

PosVec Input::MouseInput::mouse = PosVec();
PosVec Input::MouseInput::mouseWin = PosVec();
MouseClickType Input::MouseInput::mouseClickType = MouseClickType();
int Input::MouseInput::mouseInputs = 0;
float Input::MouseInput::wheelRot = 0;

int Input::MouseInput::GetClick(int _button) {
  switch (_button)  // MOUSE_INPUT_XX
  {
    case GLUT_LEFT_BUTTON:
      return mouseClickType.left;
    case GLUT_RIGHT_BUTTON:
      return mouseClickType.right;
    case GLUT_MIDDLE_BUTTON:
      return mouseClickType.middle;
    default:
      return -1;
  }
  return -1;
}

void Input::MouseInput::UpdateClick(int* _value, int _andValue) {
  if ((mouseInputs & _andValue) != 0) {
    if (*_value >= PressFrame::FIRST) {
      *_value = PressFrame::MUCH;
    } else {
      *_value = PressFrame::FIRST;
    }
  } else {
    if (*_value == PressFrame::MUCH) *_value = PressFrame::RELEASE;
    *_value = PressFrame::ZERO;
  }
}

void Input::MouseInput::UpdateMouseState(int _button, int _state) {
  int state;
  switch (_state) {
    case GLUT_DOWN:
      state = PressFrame::FIRST;
      break;
    case GLUT_UP:
      state = PressFrame::ZERO;
      break;
    default:
      break;
  }
  switch (_button) {
    case GLUT_LEFT_BUTTON:
      mouseClickType.left = state;
      break;
    case GLUT_RIGHT_BUTTON:
      mouseClickType.right = state;
      break;
    case GLUT_MIDDLE_BUTTON:
      mouseClickType.middle = state;
      break;
  }
}