#include "ObjectOverlapping.hpp"

Obj::Object2D* Obj::ObjectOverlapping::object = nullptr;

bool Obj::ObjectOverlapping::UpdateObject(Object2D* _object) {
  object = _object;
  return true;
}
