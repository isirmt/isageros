#pragma once
#include "Object2D.hpp"
// #include "MouseInput.h"
// #include "ObjectOverlapping.h"
// #include "PressFrameEnum.h"
// #include "RectangleObject.h"
// #include "TextObject.h"
#include <string>
namespace Obj {
class Button : public Object2D {
 public:
  Button(PosVec _pos, PosVec _size, bool _enabledFill = true,
               bool _enabledOutline = false)
      : Object2D(_pos, _size),
        enabledFill(_enabledFill),
        enabledOutline(_enabledOutline),
        innerColor(0),
        selectedInnerColor(0),
        hoveredInnerColor(0),
        clickedInnerColor(0),
        outerColor(0),
        selectedOuterColor(0),
        hoveredOuterColor(0),
        clickedOuterColor(0),
        outlineWidth(0) {}

  Button()
      : Object2D(PosVec(), PosVec()),
        enabledFill(true),
        enabledOutline(false),
        innerColor(0),
        selectedInnerColor(0),
        hoveredInnerColor(0),
        clickedInnerColor(0),
        outerColor(0),
        selectedOuterColor(0),
        hoveredOuterColor(0),
        clickedOuterColor(0),
        outlineWidth(0) {}

  // 色有効化無効化
  bool SetEnabledFill(bool _enabled) {
    enabledFill = _enabled;
    return true;
  }
  bool SetEnabledFill() { return enabledFill; }
  bool SetEnabledOutline(bool _enabled, float _outlineWidth = -1.f) {
    enabledOutline = _enabled;
    outlineWidth = _outlineWidth ? _outlineWidth <= 0.f : 0.f;
    return true;
  }
  // 判定用リターン
  bool SetEnabledOutline() { return enabledOutline; }

  // 色情報登録等
  bool SetInnerColor(Color255 _innerColor, bool _defaultFill = true) {
    innerColor = _innerColor;
    hoveredInnerColor = _innerColor;
    clickedInnerColor = _innerColor;
    selectedInnerColor = _innerColor;
    if (_defaultFill) {
      innerAnimation.current = innerColor;
      innerAlphaAnimation.current = (float)innerColor.a;
    }
    disabledInnerColor =
        Color255(innerColor.r, innerColor.g, innerColor.b, innerColor.a / 5.);
    return true;
  }
  bool SetInnerColor(Color255 _innerColor, Color255 _hoveredColor,
                     Color255 _clickedColor, Color255 _selectedColor,
                     bool _defaultFill = true) {
    innerColor = _innerColor;
    hoveredInnerColor = _hoveredColor;
    clickedInnerColor = _clickedColor;
    selectedInnerColor = _selectedColor;
    if (_defaultFill) {
      innerAnimation.current = innerColor;
      innerAlphaAnimation.current = (float)innerColor.a;
    }
    disabledInnerColor =
        Color255(innerColor.r, innerColor.g, innerColor.b, innerColor.a / 5.);
    return true;
  }
  // アウトラインを表示する際はtrueになっているかをチェック
  bool SetOutlineColor(Color255 _outerColor, float _outlineWidth,
                       bool _defaultFill = true) {
    outerColor = _outerColor;
    hoveredOuterColor = _outerColor;
    clickedOuterColor = _outerColor;
    selectedOuterColor = _outerColor;
    outlineWidth = _outlineWidth;
    if (_defaultFill) {
      outerAnimation.current = outerColor;
      outerAlphaAnimation.current = (float)outerColor.a;
    }
    disabledOuterColor =
        Color255(outerColor.r, outerColor.g, outerColor.b, outerColor.a / 5.);
    return true;
  }
  // アウトラインを表示する際はtrueになっているかをチェック
  bool SetOutlineColor(Color255 _outerColor, Color255 _hoveredColor,
                       Color255 _clickedColor, Color255 _selectedColor,
                       float _outlineWidth, bool _defaultFill = true) {
    outerColor = _outerColor;
    hoveredOuterColor = _hoveredColor;
    clickedOuterColor = _clickedColor;
    selectedOuterColor = _selectedColor;
    outlineWidth = _outlineWidth;
    if (_defaultFill) {
      outerAnimation.current = outerColor;
      outerAlphaAnimation.current = (float)outerColor.a;
    }
    disabledOuterColor =
        Color255(outerColor.r, outerColor.g, outerColor.b, outerColor.a / 5.);
    return true;
  }

  Color255* GetColor(ColorType type) {
    switch (type) {
      case ColorType::INNER:
        return &innerColor;
      case ColorType::HOVERED:
        return &hoveredInnerColor;
      case ColorType::CLICKED:
        return &clickedInnerColor;
      case ColorType::SELECTED:
        return &selectedInnerColor;
      case ColorType::OUTER_INNER:
        return &outerColor;
      case ColorType::OUTER_HOVERED:
        return &hoveredOuterColor;
      case ColorType::OUTER_CLICKED:
        return &clickedOuterColor;
      case ColorType::OUTER_SELECTED:
        return &selectedOuterColor;
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
  void EventRectSetVector();

 private:
  Color255 innerColor;
  Color255 hoveredInnerColor;
  Color255 clickedInnerColor;
  Color255 selectedInnerColor;
  Color255 outerColor;
  Color255 hoveredOuterColor;
  Color255 clickedOuterColor;
  Color255 selectedOuterColor;

  Color255 disabledInnerColor;
  Color255 disabledOuterColor;

  float outlineWidth;

  bool enabledFill;
  bool enabledOutline;
};

}  // namespace Obj