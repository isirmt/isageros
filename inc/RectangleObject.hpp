#pragma once
#include "MouseInput.hpp"
#include "Object2D.hpp"
// #include "ObjectOverlapping.h"

namespace Obj {
class Rectangle : public Object2D {
 public:
  inline Rectangle(PosVec _pos, PosVec _size, bool _enabledFill = true,
                  bool _enabledOutline = false)
      : Object2D(_pos, _size),
        enabledFill(_enabledFill),
        enabledOutline(_enabledOutline),
        innerColor(0),
        outerColor(0),
        outlineWidth(0),
        currentInnerColor(0) {}

  inline Rectangle()
      : Object2D(PosVec(), PosVec()),
        enabledFill(true),
        enabledOutline(false),
        innerColor(0),
        outerColor(0),
        outlineWidth(0),
        currentInnerColor(0) {}

  // 色有効化無効化
  inline bool SetEnabledFill(bool _enabled) {
    enabledFill = _enabled;
    return true;
  }
  inline bool SetEnabledFill() { return enabledFill; }
  inline bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) {
    enabledOutline = _enabled;
    outlineWidth = (enabledOutline) ? _outlineWidth : 0;
    return true;
  }
  inline bool SetEnabledOutline() { return enabledOutline; }

  // 色情報登録等
  inline bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true) {
    innerColor = _innerColor;
    if (_defaultFill) {
      innerAnimation.current = innerColor;
      innerAlphaAnimation.current = (float)innerColor.a;
    }
    return true;
  }
  // アウトラインを表示する際はtrueになっているかをチェック
  inline bool SetOutlineColor(Color255 _outerColor, float _outlineWidth,
                       bool _defaultFill = true) {
    outerColor = _outerColor;
    if (_defaultFill) {
      outerAnimation.current = outerColor;
      outerAlphaAnimation.current = (float)outerColor.a;
    }
    return true;
  }

  inline Color255* GetColor(ColorType type) {
    switch (type) {
      case ColorType::INNER:
        return &innerColor;
      case ColorType::OUTER_INNER:
        return &outerColor;
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

  Color255 outerColor;
  float outlineWidth;

  bool enabledFill;
  bool enabledOutline;

  Color255 currentInnerColor;
};

}  // namespace Obj