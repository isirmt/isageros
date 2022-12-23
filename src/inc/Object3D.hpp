#pragma once
#include <GL/glut.h>

#include "Color255.hpp"
#include "PositionVector.hpp"

namespace Obj {
class Object3D {
 public:
  Object3D(){};
  Object3D(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec())
      : r(_r),
        v(_v),
        a(_a),
        dt(0),
        scale(1.f, 1.f, 1.f),
        deg(0.f),
        rotScale(0.f, 0.f, 0.f){};
  ~Object3D(){};

  virtual void Update() = 0;
  virtual void Draw() = 0;

  void SetAmbient(Color255 _ambient) { ambient = _ambient; }
  void SetDiffuse(Color255 _diffuse) { diffuse = _diffuse; }
  void SetSpecular(Color255 _specular) { specular = _specular; }
  void SetEmission(Color255 _emission) { emission = _emission; }
  // 0~127
  void SetShininess(float _shininess) { shininess[0] = _shininess; }
  void SetScale(PosVec _scale = PosVec(1.f, 1.f, 1.f)) { scale = _scale; }
  // 位置を変えるだけ
  void SetPosition(PosVec _r) { r = _r; }
  // 速度を変えるだけ
  void SetVelocity(PosVec _v) { v = _v; }
  // 加速度を変えるだけ
  void SetAcceleration(PosVec _a) { a = _a; }
  void SetRotate(float _deg = 0.f, PosVec _rotScale = PosVec()) {
    deg = _deg;
    rotScale = _rotScale;
  }

 protected:
  PosVec r;
  PosVec v;
  PosVec a;

  PosVec scale;
  float deg;
  PosVec rotScale;

  float t;
  double dt;  // need timedelta

  Color255 ambient;
  Color255 diffuse;
  Color255 specular;
  Color255 emission;

  float shininess[1];
};

}  // namespace Obj