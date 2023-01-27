#pragma once
#include "Object3D.hpp"

namespace Obj {
class Teapot : public Object3D {
 public:
  Teapot();
  Teapot(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec());
  ~Teapot();

  void Update() override;
  void Draw() override;
};
}  // namespace Obj