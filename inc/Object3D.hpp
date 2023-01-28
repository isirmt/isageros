#pragma once
#include <GL/glut.h>
#include <vector>

#include "Color255.hpp"
#include "PositionVector.hpp"
#include "Time.hpp"

namespace Obj {
class Object3D {
 public:
  Object3D(){};
  Object3D(PosVec _r, PosVec _v = PosVec(), PosVec _a = PosVec())
      : r(_r),
        v(_v),
        a(_a),
        t(0),
        dt(0),
        scale(1.f, 1.f, 1.f),
        deg(0.f),
        rotScale(0.f, 0.f, 0.f),
        isMultiRotates(false){};
  ~Object3D(){};

  virtual void Update() = 0;
  virtual void Draw() = 0;

  inline void SetMultiRotates(bool _flag) { isMultiRotates = _flag; }
  inline void AddMultiRotates(float _deg = 0.f, PosVec _rotScale = PosVec()) {
    degs.emplace_back(_deg);
    rotScales.emplace_back(_rotScale);
  }
  inline void ClearRotates() {
    degs.clear();
    rotScales.clear();
  }
  inline void SetAmbient(Color255 _ambient) { ambient = _ambient; }
  inline void SetDiffuse(Color255 _diffuse) { diffuse = _diffuse; }
  inline void SetSpecular(Color255 _specular) { specular = _specular; }
  inline void SetEmission(Color255 _emission) { emission = _emission; }
  // 0~127
  inline void SetShininess(float _shininess) { shininess[0] = _shininess; }
  inline void SetScale(PosVec _scale = PosVec(1.f, 1.f, 1.f)) { scale = _scale; }
  // 位置を変えるだけ
  inline void SetPosition(PosVec _r) { r = _r; }
  // 速度を変えるだけ
  inline void SetVelocity(PosVec _v) { v = _v; }
  // 加速度を変えるだけ
  inline void SetAcceleration(PosVec _a) { a = _a; }
  inline void SetRotate(float _deg = 0.f, PosVec _rotScale = PosVec()) {
    deg = _deg;
    rotScale = _rotScale;
  }

  inline Color255 GetAmbient() { return ambient; }
  inline Color255* GetAmbientPointer() { return &ambient; }
  inline Color255 GetDiffuse() { return diffuse; }
  inline Color255* GetDiffusePointer() { return &diffuse; }
  inline Color255 GetSpecular() { return specular; }
  inline Color255* GetSpecularPointer() { return &specular; }
  inline Color255 GetEmission() { return emission; }
  inline float GetShininess() { return shininess[0]; }
  inline PosVec GetScale() { return scale; }
  inline PosVec* GetScalePointer() { return &scale; }
  inline PosVec GetPosition() { return r; }
  inline PosVec* GetPositionPointer() { return &r; }
  inline PosVec GetVelocity() { return v; }
  inline PosVec* GetVelocityPointer() { return &v; }
  inline PosVec GetAcceleration() { return a; }
  inline PosVec* GetAccelerationPointer() { return &a; }
  inline float GetRotateDegree() { return deg; }
  inline PosVec GetRotateScale() { return rotScale; }
  inline PosVec* GetRotateScalePointer() { return &rotScale; }

 protected:
  PosVec r;
  PosVec v;
  PosVec a;

  PosVec scale;
  float deg;
  PosVec rotScale;

  std::vector<float> degs;
  std::vector<PosVec> rotScales;

  float t;
  double dt;  // need timedelta

  Color255 ambient;
  Color255 diffuse;
  Color255 specular;
  Color255 emission;

  float shininess[1];

  bool isMultiRotates;
};

}  // namespace Obj