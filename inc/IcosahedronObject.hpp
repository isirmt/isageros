#pragma once
#include "Object3D.hpp"

namespace Obj {
class Icosahedron : public Object3D {
 public:
  Icosahedron();
  Icosahedron(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec());
  ~Icosahedron();

  void Update() override;
  void Draw() override;
};
}  // namespace Obj