#pragma once
#include <GL/glut.h>

#include <map>

#include "Color255.hpp"
#include "PositionVector.hpp"

namespace Scene {
struct Light {
  bool enabled;
  PosVec r;
  Color255 ambient;
  Color255 diffuse;
  Color255 specular;
};
class LightManager {
 public:
  static void SetActiveLighting(bool _beLighting) {
    beLighting = _beLighting;
    if (beLighting)
      glEnable(GL_LIGHTING);
    else
      glDisable(GL_LIGHTING);
  }
  static void SetActive(int _num, bool _enabled) {
    lights[_num].enabled = _enabled;
    if (lights[_num].enabled)
      glEnable(_num);
    else
      glDisable(_num);
  }
  static void Set(int _num, PosVec _r, Color255 _ambient = Color255(),
                  Color255 _diffuse = Color255(),
                  Color255 _specular = Color255()) {
    Light l;
    l.r = _r;
    l.ambient = _ambient;
    l.diffuse = _diffuse;
    l.specular = _specular;
    lights[_num] = l;
    UpdateLight(_num);
  }

  static Light GetLight(int _num) {
    auto it = lights.find(_num);
    return lights[_num];
  }

  static void UpdateLight(int _num) {
    ParamSet(_num, lights[_num].ambient, GL_AMBIENT);
    ParamSet(_num, lights[_num].diffuse, GL_DIFFUSE);
    ParamSet(_num, lights[_num].specular, GL_SPECULAR);
    ParamSet(_num, lights[_num].r, GL_POSITION);
  }

 private:
  static void ParamSet(int _num, Color255& _color, int glparam) {
    GLfloat param[4];
    param[0] = _color.r;
    param[1] = _color.g;
    param[2] = _color.b;
    param[3] = _color.a;
    glLightfv(_num, glparam, param);
  }
  static void ParamSet(int _num, PosVec& _pos, int glparam) {
    GLfloat param[4];
    param[0] = _pos.x;
    param[1] = _pos.y;
    param[2] = _pos.z;
    param[3] = 0.;
    glLightfv(_num, glparam, param);
  }
  static std::map<int, Light> lights;
  static bool beLighting;
};
}  // namespace Scene