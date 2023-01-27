#pragma once
#include "Object3D.hpp"

namespace Obj {
class Cone : public Object3D {
 public:
  Cone();
  Cone(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec());
  ~Cone();

  void Update() override;
  void Draw() override;
};
}  // namespace Obj