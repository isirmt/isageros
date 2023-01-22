#pragma once
#include "Time.hpp"
#include "ObjectLoader.hpp"
#include "MouseInput.hpp"
#include <locale>

namespace GLSYS {
class ApplicationBuilder {
 public:
  static void Initialize();
  static void Update();
};
}  // namespace GLSYS