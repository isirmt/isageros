#include "CubeObject.hpp"

#include "Camera.hpp"
#include "Color255.hpp"

Obj::Cube::Cube() {}
Obj::Cube::Cube(PosVec _r, PosVec _v, PosVec _a)
    : Object3D::Object3D(_r, _v, _a) {}

Obj::Cube::~Cube() {}

void Obj::Cube::Update() {
  dt = Time::DeltaTime();
  t += dt;

  v.x += a.x * dt;
  v.y += a.y * dt;
  v.z += a.z * dt;

  r.x += v.x * dt;
  r.y += v.y * dt;
  r.z += v.z * dt;
}

void Obj::Cube::Draw() {
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.set);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.set);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular.set);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glTranslated(r.x, r.y, r.z);
  if (!isMultiRotates) {
    glRotatef(deg, rotScale.x, rotScale.y, rotScale.z);
  } else {
    for (int i = 0; i < rotScales.size(); i++) {
      glRotatef(degs[i], rotScales[i].x, rotScales[i].y, rotScales[i].z);
    }
  }
  glScalef(scale.x, scale.y, scale.z);
  glEnable(GL_NORMALIZE);
  glutSolidCube(10);
  glPopMatrix();
}
