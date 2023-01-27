#pragma once
#include "ImageData.hpp"
#include "ImageLoader.hpp"
#include "MouseInput.hpp"
#include "Object2D.hpp"

namespace Obj {
class Image : public Object2D {
 public:
  Image(PosVec _pos, PosVec _size, std::string _filePath);

  Image() : Object2D(PosVec(), PosVec()) {}

  // 更新描画
  void Collide() override;
  void Update() override;
  void Draw() override;

 private:
  void CollideMouse() override;

 private:
  ImageData imageData;
};

}  // namespace Obj