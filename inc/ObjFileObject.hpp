#pragma once
#include <string>

#include "Object3D.hpp"
#include "ObjectLoader.hpp"

namespace Obj {
class ObjFile : public Object3D {
 public:
  ObjFile();
  ObjFile(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec(),
          std::string _fileName = "./example.obj");
  ~ObjFile();

  void Update() override;
  void Draw() override;

 private:
  Obj::Mesh object;
};
}  // namespace Obj