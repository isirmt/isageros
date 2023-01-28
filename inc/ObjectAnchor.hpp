#include "ApplicationPreference.hpp"

namespace Obj {
class Object2DAnchor {
 public:
  inline static PosVec AnchorUpperLeft(PosVec _pos) {
    return PosVec(_pos.x, ApplicationPreference::windowSize.y - _pos.y);
  }
  inline static PosVec AnchorUpperRight(PosVec _pos) {
    return PosVec(ApplicationPreference::windowSize.x - _pos.x,
                  ApplicationPreference::windowSize.y - _pos.y);
  }
  inline static PosVec AnchorLowerLeft(PosVec _pos) { return PosVec(_pos.x, _pos.y); }
  inline static PosVec AnchorLowerRight(PosVec _pos) {
    return PosVec(ApplicationPreference::windowSize.x - _pos.x, _pos.y);
  }
};
}  // namespace Obj