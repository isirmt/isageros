#pragma once
#include <sys/stat.h>

#include <locale>

#include "MouseInput.hpp"
#include "ObjectLoader.hpp"
#include "Time.hpp"

namespace GLSYS {
class ApplicationBuilder {
 public:
  static void Initialize();
  static void Update();
};
}  // namespace GLSYS