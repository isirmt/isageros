#pragma once
#include <vector>

#include "Object2D.hpp"
#include "ObjectFuncData.hpp"
namespace Obj {
class ObjectLayer {
 public:
  ObjectLayer() {}
  ~ObjectLayer() {}

  void AddObject(Object2D* _object);
  void DeleteObject(Object2D* _object);

  void Clear();

  void SetTopLayer(Object2D* _object, int _shift = 0);
  void SetButtomLayer(Object2D* _object, int _shift = 0);

  void MoveLayer(Object2D* _object, int _distance);

  int Total() { return (int)layer.size(); }

  void Collide();
  void Update();
  void Draw();

 private:
  std::vector<ObjectFunc> layer;
};
}  // namespace Obj