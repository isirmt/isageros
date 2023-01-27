#include "CylinderObject.hpp"

#include "Camera.hpp"
#include "Color255.hpp"

Obj::Cylinder::Cylinder() {}
Obj::Cylinder::Cylinder(PosVec _r, PosVec _v, PosVec _a)
    : Object3D::Object3D(_r, _v, _a) {}

Obj::Cylinder::~Cylinder() {}

void Obj::Cylinder::Update() {
  dt = Time::DeltaTime();
  t += dt;

  v.x += a.x * dt;
  v.y += a.y * dt;
  v.z += a.z * dt;

  r.x += v.x * dt;
  r.y += v.y * dt;
  r.z += v.z * dt;
}

void Obj::Cylinder::Draw() {
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

  // r h n
  float r = 3.f;
  float h = 8.0f;
  float n = 20;
  float x, y, z, dq;
  int i;

  glEnable(GL_NORMALIZE);
  dq = M_PI * 2. / (float)n;
  y = 0.5 * h;
  glPushMatrix();
  glRotatef(-dq * 180.0 / (M_PI * 2.), 0.0, 0.1, 0.0);
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= n; i += 1) {
    x = r * cos(dq * (float)i);
    z = r * sin(dq * (float)i);
    glNormal3f(x, 0, z);
    glVertex3f(x, y, z);
    glVertex3f(x, -y, z);
  }
  glEnd();
  glBegin(GL_POLYGON);
  glNormal3f(0.0, -1.0, 0.0);
  for (i = 0; i < n; i += 1) {
    x = r * cos(dq * (float)i);
    z = r * sin(dq * (float)i);
    glVertex3f(x, -y, z);
  }
  glEnd();
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 1.0, 0.0);
  for (i = 0; i < n; i += 1) {
    x = r * cos(dq * (float)i);
    z = r * sin(dq * (float)i);
    glVertex3f(x, y, z);
  }
  glEnd();
  glPopMatrix();
  glDisable(GL_NORMALIZE);

  glPopMatrix();
}