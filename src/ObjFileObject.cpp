#include "ObjFileObject.hpp"

#include "Camera.hpp"
#include "Color255.hpp"

Obj::ObjFile::ObjFile() {}
Obj::ObjFile::ObjFile(PosVec _r, PosVec _v, PosVec _a, std::string _fileName)
    : Object3D::Object3D(_r, _v, _a) {
  object.Load(_fileName.c_str());
  // object.PrintInformation();
}

Obj::ObjFile::~ObjFile() {}

void Obj::ObjFile::Update() {
  dt = Time::DeltaTime();
  t += dt;

  v.x += a.x * dt;
  v.y += a.y * dt;
  v.z += a.z * dt;

  r.x += v.x * dt;
  r.y += v.y * dt;
  r.z += v.z * dt;
}

void Obj::ObjFile::Draw() {
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.set);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.set);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular.set);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glTranslated(r.x, r.y, r.z);
  glRotatef(deg, rotScale.x, rotScale.y, rotScale.z);
  glScalef(scale.x, scale.y, scale.z);
  glEnable(GL_NORMALIZE);
  object.Render(20);
  glPopMatrix();
}
