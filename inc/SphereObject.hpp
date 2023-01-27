#pragma once
#include "Object3D.hpp"

namespace Obj {
class Sphere : public Object3D {
 public:
  Sphere();
  Sphere(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec());
  ~Sphere();

  void Update() override;
  void Draw() override;
};
}  // namespace Obj