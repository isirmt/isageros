#include "SphereObject.hpp"

#include "Color255.hpp"
#include "Camera.hpp"

Obj::Sphere::Sphere() {}
Obj::Sphere::Sphere(PosVec _r, PosVec _v, PosVec _a)
    : Object3D::Object3D(_r, _v, _a) {}

Obj::Sphere::~Sphere() {}

void Obj::Sphere::Update() {
  dt = Time::DeltaTime();
  t += dt;

  v.x += a.x * dt;
  v.y += a.y * dt;
  v.z += a.z * dt;

  r.x += v.x * dt;
  r.y += v.y * dt;
  r.z += v.z * dt;
}

void Obj::Sphere::Draw() {
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
  glutSolidSphere(5.,30,30); 
  glPopMatrix();
}