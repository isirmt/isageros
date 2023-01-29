#pragma once
#include <math.h>

#include "Object3D.hpp"

namespace Obj {
class Cylinder : public Object3D {
 public:
  Cylinder();
  Cylinder(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec());
  ~Cylinder();

  void Update() override;
  void Draw() override;
};
}  // namespace Obj