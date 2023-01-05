#include "MouseInput.hpp"

PosVec Input::MouseInput::mouse = PosVec();
PosVec Input::MouseInput::mouseWin = PosVec();
MouseClickType Input::MouseInput::mouseClickType = MouseClickType();
MouseClickType Input::MouseInput::mouseFirstQueue = MouseClickType();
float Input::MouseInput::wheelRot = 0;

void Input::MouseInput::Update() {
  UpdateClick(&mouseClickType.left, &mouseFirstQueue.left);
  UpdateClick(&mouseClickType.right, &mouseFirstQueue.right);
  UpdateClick(&mouseClickType.middle, &mouseFirstQueue.middle);

  // wheelRot
}

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

void Input::MouseInput::UpdateClick(int* _value, int* _andValue) {
  if (*_value >= PressFrame::FIRST) {
    *_value = PressFrame::MUCH;
  }
  if (*_andValue == PressFrame::FIRST) {
    *_value = PressFrame::FIRST;
    *_andValue = PressFrame::ZERO;
  } else if (*_andValue == PressFrame::RELEASE) {
    *_value = PressFrame::ZERO;
    *_andValue = PressFrame::ZERO;
  }
}

void Input::MouseInput::UpdateMouseState(int _button, int _state) {
  int state;
  switch (_state) {
    case GLUT_DOWN:
      state = PressFrame::FIRST;
      break;
    case GLUT_UP:
      state = PressFrame::RELEASE;
      break;
    default:
      break;
  }
  switch (_button) {
    case GLUT_LEFT_BUTTON:
      mouseFirstQueue.left = state;
      break;
    case GLUT_RIGHT_BUTTON:
      mouseFirstQueue.right = state;
      break;
    case GLUT_MIDDLE_BUTTON:
      mouseFirstQueue.middle = state;
      break;
  }
}