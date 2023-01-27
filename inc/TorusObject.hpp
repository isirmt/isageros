#pragma once
#include "Object3D.hpp"

namespace Obj {
class Torus : public Object3D {
 public:
  Torus();
  Torus(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec());
  ~Torus();

  void Update() override;
  void Draw() override;
};
}  // namespace Obj