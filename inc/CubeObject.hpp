#pragma once
#include "Object3D.hpp"

namespace Obj {
class Cube : public Object3D {
 public:
  Cube();
  Cube(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec());
  ~Cube();

  void Update() override;
  void Draw() override;
};
}  // namespace Obj