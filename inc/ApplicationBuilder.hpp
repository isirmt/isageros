#pragma once
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

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