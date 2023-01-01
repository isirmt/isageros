#include "TeapotObject.hpp"

#include "Color255.hpp"
#include "Camera.hpp"

Obj::Teapot::Teapot() {}
Obj::Teapot::Teapot(PosVec _r, PosVec _v, PosVec _a)
    : Object3D::Object3D(_r, _v, _a) {}

Obj::Teapot::~Teapot() {}

void Obj::Teapot::Update() {
  dt = Time::DeltaTime();
  t += dt;

  v.x += a.x * dt;
  v.y += a.y * dt;
  v.z += a.z * dt;

  r.x += v.x * dt;
  r.y += v.y * dt;
  r.z += v.z * dt;
}

void Obj::Teapot::Draw() {
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.set);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.set);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular.set);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glTranslated(r.x, r.y, r.z);
  glRotatef(deg, rotScale.x, rotScale.y, rotScale.z);
  glScalef(scale.x, scale.y, scale.z);
  glEnable(GL_NORMALIZE);
  glutSolidTeapot(5.0);
  glPopMatrix();
}