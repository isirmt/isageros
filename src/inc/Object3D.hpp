#pragma once
#include <GL/glut.h>

#include "Color255.hpp"
#include "PositionVector.hpp"

namespace Obj {
class Object3D {
 public:
  Object3D(){};
  Object3D(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec())
      : r(_r), v(_v), a(_a), dt(0){};
  ~Object3D(){};

  virtual void Update() = 0;
  virtual void Draw() = 0;

  void SetAmbient(Color255 _ambient) { ambient = _ambient; }
  void SetDiffuse(Color255 _diffuse) { diffuse = _diffuse; }
  void SetSpecular(Color255 _specular) { specular = _specular; }
  void SetEmission(Color255 _emission) { emission = _emission; }
  // 0~127
  void SetShininess(float _shininess) { shininess[0] = _shininess; }

 protected:
  PosVec r;
  PosVec v;
  PosVec a;

  float t;
  double dt;  // need timedelta

  Color255 ambient;
  Color255 diffuse;
  Color255 specular;
  Color255 emission;

  float shininess[1];
};

}  // namespace Obj