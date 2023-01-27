#pragma once
#include "Object3D.hpp"

namespace Obj {
class Dodecahedron : public Object3D {
 public:
  Dodecahedron();
  Dodecahedron(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec());
  ~Dodecahedron();

  void Update() override;
  void Draw() override;
};
}  // namespace Obj