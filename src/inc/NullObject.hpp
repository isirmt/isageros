#pragma once
#include "Object2D.hpp"

namespace Obj {

class Null : public Object2D {
 public:
  // pos1は始点,pos2は終点
  Null(PosVec _pos1, PosVec _pos2)
      : Object2D(_pos1, _pos2) {}
  Null() : Object2D(PosVec(), PosVec()) {}

  // 更新描画
  void Collide() {}
  void Update() override;
  void Draw() {}

 private:
  void CollideMouse() override {}
};

}  // namespace Obj