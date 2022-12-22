#include "inc/TitleScene.hpp"

void draw_cube(float *a, float *d, float *s);

void Scene::TitleScene::Update() {
  deg += .1f;
  return;
}

void Scene::TitleScene::Draw() {
  // write here.
  float ambient[4], diffuse[4], specular[4];
  glPushMatrix();
  glTranslatef(0.0, 5., 0.0);
  glRotatef(deg, 1.0, 0.7, 0.0);
  glScalef(12, 10, 12);
  glEnable(GL_NORMALIZE);
  boxAmbient = Color255(114, 235, 209);
  ambient[0] = boxAmbient.r;
  ambient[1] = boxAmbient.g;
  ambient[2] = boxAmbient.b;
  ambient[3] = boxAmbient.a;
  diffuse[0] = .3;
  diffuse[1] = .3;
  diffuse[2] = .3;
  diffuse[3] = .3;
  specular[0] = 1.0;
  specular[1] = 1.0;
  specular[2] = 1.0;
  specular[3] = 1.0;
  draw_cube(ambient, diffuse, specular);
  glPopMatrix();
}