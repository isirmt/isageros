#include "TitleScene.hpp"

Scene::TitleScene::TitleScene() {
  Camera::SetActive(true);
  SceneBase::SetOrthoCameraWindow();
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();
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
  centerCube.SetScale(PosVec(25, 25, 25));
  centerCube.SetShininess(20);
  centerCube.SetRotate(deg, PosVec(0, 1, 0));

  character = Obj::ObjFile(PosVec(700, -500, 0.0), PosVec(), PosVec(),
                            "Mesh/test.obj");
  character.SetScale(PosVec(17, 17, 17));
  character.SetShininess(10);
  character.SetRotate(deg, PosVec(0, 1, 0));

  button = new Obj::Button(PosVec(30, 30), PosVec(300, 500), true, true);
  button->SetInnerColor(Color255(255, 100, 50), Color255(230, 80, 70),
                       Color255(200, 50, 50), Color255(100, 100, 100));
  button->SetOutlineColor(Color255(35, 57, 40), 5.f);
  button->SetInnerAnimation(.2f);

  rect = new Obj::Rectangle(PosVec(700, 200), PosVec(100, 100), true, true);
  rect->SetInnerColor(Color255(200, 70, 130));
  rect->SetOutlineColor(Color255(35, 57, 40), 5.f);

  text = new Obj::Text(PosVec(500,500), PosVec(), "こんにちは");
  text->SetInnerColor(Color255(200, 70, 130));

  layer2D.AddObject(button);
  layer2D.AddObject(rect);
  layer2D.AddObject(text);
}

void Scene::TitleScene::Update() {
  layer2D.Collide();

  deg += 150 * Time::DeltaTime();
  if (deg > 360) deg -= 360;

  centerCube.SetRotate(deg, centerCube.GetRotateScale());
  character.SetRotate(deg, centerCube.GetRotateScale());

  sphere.Update();
  cube.Update();
  centerCube.Update();
  character.Update();

  layer2D.Update();
}

void Scene::TitleScene::Draw() {
  SceneBase::Set3DDrawMode();
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  glPushMatrix();
  sphere.Draw();
  cube.Draw();
  {
    glPushMatrix();
    glRotatef(30,1,0,0);
    centerCube.Draw();
    glPopMatrix();
  }
  character.Draw();
  glPopMatrix();

  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();
}