#pragma once
#include <GL/gl.h>
#include <GL/glut.h>

#include "ApplicationPreference.hpp"
#include "LightManager.hpp"

namespace GLSYS {
class GLBuilder {
 public:
  static void GLSetup();
  static void LightSetup();

  static void DrawInitialize();
};
}  // namespace GLSYS