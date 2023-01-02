#include "TitleScene.hpp"

Scene::TitleScene::TitleScene() {
  Camera::SetActive(true);
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  deg = 0.f;
  sphere = Obj::Sphere(PosVec(-50.0, 350, 20.0), PosVec(50, 200, 0.0),
                       PosVec(0.0, -300, 0.0));
  sphere.SetAmbient(Color255(150, 235, 80));
  sphere.SetDiffuse(Color255(.5f, .5f, .5f));
  sphere.SetSpecular(Color255(255, 255, 255, 255));
  sphere.SetShininess(20);
  sphere.SetScale(PosVec(10, 10, 10));

  cube = Obj::Cube(PosVec(-40.0, 10., 0.0), PosVec(500, 7, 0.0),
                   PosVec(0, -300, 0.0));
  cube.SetAmbient(Color255(100, 75, 80));
  cube.SetDiffuse(Color255(.3f, .3f, .3f));
  cube.SetSpecular(Color255(255, 255, 255, 255));
  cube.SetScale(PosVec(10, 10, 10));
  cube.SetShininess(20);
  cube.SetRotate(30, PosVec(.5, .7, 0));

  centerCube = Obj::ObjFile(PosVec(0.0, 5., 0.0), PosVec(), PosVec(),
                            "Mesh/forest1.obj");
  centerCube.SetAmbient(Color255(114, 235, 209));
  centerCube.SetDiffuse(Color255(.3f, .3f, .3f));
  centerCube.SetSpecular(Color255(1.f, 1.f, 1.f, 1.f));
  centerCube.SetScale(PosVec(10, 10, 10));
  centerCube.SetShininess(20);
  centerCube.SetRotate(deg, PosVec(.5, 1, .5));
}

void Scene::TitleScene::Update() {
  deg += 360 * Time::DeltaTime();
  if (deg > 360) deg -= 360;

  centerCube.SetRotate(deg, centerCube.GetRotateScale());

  sphere.Update();
  cube.Update();
  centerCube.Update();
}

void Scene::TitleScene::Draw() {
  sphere.Draw();
  cube.Draw();
  centerCube.Draw();
}