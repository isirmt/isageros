#pragma once
#include <vector>

#include "Object2D.hpp"

namespace Obj {
struct ObjectFunc {
  Object2D* object;

  ObjectFunc(Object2D* _object) : object(_object) {}
};
}  // namespace Obj