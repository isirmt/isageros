#include "inc/SphereObject.hpp"

#include "inc/Color255.hpp"

Obj::Sphere::Sphere() {}
Obj::Sphere::Sphere(PosVec _r, PosVec _v, PosVec _a)
    : Object3D::Object3D(_r, _v, _a) {}

Obj::Sphere::~Sphere() {}

void Obj::Sphere::Update() {
  if (hasGravity) {
    t = dt * double(tn);

    v.x += a.x * dt;
    v.y += a.y * dt;
    v.z += a.z * dt;

    r.x += v.x * dt;
    r.y += v.y * dt;
    r.z += v.z * dt;
    tn++;
  }
}

void Obj::Sphere::Draw() {
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.set);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.set);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular.set);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glTranslated(r.x, r.y, r.z);
  glScalef(10,10,10);
  glEnable(GL_NORMALIZE);
  glutSolidSphere(4.0, 20, 20);
  glPopMatrix();
}
