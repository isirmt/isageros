#pragma once
#include "MouseInput.hpp"
#include "Object2D.hpp"
#include "jfont.hpp"
// #include "ObjectOverlapping.h"

namespace Obj {
class Text : public Object2D {
 public:
  Text(PosVec _pos, PosVec _size, std::string _text, bool _enabledFill = true)
      : Object2D(_pos, _size),
        enabledFill(_enabledFill),
        innerColor(0),
        currentInnerColor(0),
        text(_text) {}

  Text()
      : Object2D(PosVec(), PosVec()),
        enabledFill(true),
        innerColor(0),
        currentInnerColor(0),
        text() {}

  void SetString(std::string _text) {
    text = _text;
  }

  // 色有効化無効化
  bool SetEnabledFill(bool _enabled) {
    enabledFill = _enabled;
    return true;
  }
  bool SetEnabledFill() { return enabledFill; }

  // 色情報登録等
  bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true) {
    innerColor = _innerColor;
    if (_defaultFill) {
      innerAnimation.current = innerColor;
      innerAlphaAnimation.current = (float)innerColor.a;
    }
    return true;
  }

  Color255* GetColor(ColorType type) {
    switch (type) {
      case ColorType::INNER:
        return &innerColor;
      default:
        return nullptr;
    }
  }

  // 更新描画
  void Collide() override;
  void Update() override;
  void Draw() override;

 private:
  void CollideMouse() override;

 private:
  Color255 innerColor;

  bool enabledFill;

  Color255 currentInnerColor;

  std::string text;
};

}  // namespace Obj