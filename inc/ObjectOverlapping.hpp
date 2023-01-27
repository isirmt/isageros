#pragma once
#include "Object2D.hpp"

namespace Obj {
class ObjectOverlapping {
 public:
  static bool Reset() { return true; }
  static bool UpdateObject(
      Object2D* _object);  // SetNoMouse() メソッドを持っている必要あり
  static Object2D* GetCurrentObj() { return object; }

 private:
  static Object2D* object;
};

}  // namespace Obj