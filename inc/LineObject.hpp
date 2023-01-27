#pragma once
#include "Object2D.hpp"

namespace Obj {

class Line : public Object2D {
 public:
  // pos1は始点,pos2は終点
  Line(PosVec _pos1, PosVec _pos2, bool _enabledOutline = true)
      : Object2D(_pos1, _pos2),
        enabledOutline(_enabledOutline),
        outerColor(0),
        outlineWidth(1.f) {}
  Line()
      : Object2D(PosVec(), PosVec()),
        enabledOutline(false),
        outerColor(0),
        outlineWidth(1.f) {}

  bool SetEnabledOutline(bool _enabled, float _outlineWidth = 1) {
    enabledOutline = _enabled;
    outlineWidth = (enabledOutline) ? _outlineWidth : 0;
    return true;
  }
  bool SetEnabledOutline() { return enabledOutline; }

  bool SetOutlineColor(Color255 _outerColor, float _outlineWidth) {
    outerColor = _outerColor;
    outlineWidth = _outlineWidth;
    return true;
  }

  // 更新描画
  void Collide() override;
  void Update() override;
  void Draw() override;

 private:
  void CollideMouse() override {}

 private:
  Color255 outerColor;
  float outlineWidth;

  bool enabledOutline;
};

}  // namespace Obh