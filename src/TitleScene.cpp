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
  fdeg = 150.f;
  sphere = Obj::Sphere(PosVec(0, 100, 0), PosVec(0, 0, 0.0),
                       PosVec(0.0, 0, 0.0));
  sphere.SetAmbient(Color255(150, 235, 80));
  sphere.SetDiffuse(Color255(.5f, .5f, .5f));
  sphere.SetSpecular(Color255(255, 255, 255, 255));
  sphere.SetShininess(20);
  sphere.SetScale(PosVec(1, 1, 1));

  cube = Obj::Cube(PosVec(-40.0, 10., 0.0), PosVec(500, 7, 0.0),
                   PosVec(0, -300, 0.0));
  cube.SetAmbient(Color255(100, 75, 80));
  cube.SetDiffuse(Color255(.3f, .3f, .3f));
  cube.SetSpecular(Color255(255, 255, 255, 255));
  cube.SetScale(PosVec(10, 10, 10));
  cube.SetShininess(20);
  cube.SetRotate(30, PosVec(.5, .7, 0));

  centerCube = Obj::ObjFile(PosVec(0.0, 5., 0.0), PosVec(), PosVec(),
                            "Mesh/tabletennis_stage.obj");
  centerCube.SetScale(PosVec(100, 100, 100));
  centerCube.SetShininess(20);
  centerCube.SetRotate(0, PosVec(0, 1, 0));

  character =
      Obj::ObjFile(PosVec(100, 0, 0.0), PosVec(), PosVec(), "Mesh/chara.obj");
  character.SetScale(PosVec(5, 5, 5));
  character.SetShininess(10);
  character.SetRotate(deg, PosVec(0, 1, 0));

  button = new Obj::Button(PosVec(30, 30), PosVec(200, 200), true, true);
  button->SetInnerColor(Color255(255, 100, 50), Color255(230, 80, 70),
                        Color255(200, 50, 50), Color255(100, 100, 100));
  button->SetOutlineColor(Color255(35, 57, 40), 5.f);
  button->SetInnerAnimation(.2f);

  rect = new Obj::Rectangle(PosVec(700, 200), PosVec(100, 100), true, true);
  rect->SetInnerColor(Color255(200, 70, 130));
  rect->SetOutlineColor(Color255(35, 57, 40), 5.f);

  text = new Obj::Text(PosVec(500, 500), PosVec(), "テーブルテニス 卓球 Table_Tennis\nサンプルテキスト");
  text->SetInnerColor(Color255(250, 250, 250));

  layer2D.AddObject(button);
  // layer2D.AddObject(rect);
  layer2D.AddObject(text);

  Scene::LightManager::Set(
      GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5,0.5,0.5, 1.f),
      Color255(1.f, 1.f, 1.f, 1.0f), Color255(0.0f, 0.0f, 0.0f, 1.f));

  // Scene::LightManager::Set(
  //     GL_LIGHT1, PosVec(250, 100, 250), Color255(0.f, 0.f, 0.f, .5f),
  //     Color255(1.f, 1.f, 1.f, 1.0f), Color255(1.f, 1.f, 1.f, 1.f));

  // Scene::LightManager::SetActive(GL_LIGHT1, true);
}

void Scene::TitleScene::Update() {
  layer2D.Collide();

  deg += fdeg * Time::DeltaTime();
  if (deg > 600 || deg < 0) {
    deg -= fdeg * Time::DeltaTime() * 2.f;
    fdeg *= -1.f;
  }

  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(700, 600, 450 - deg), PosVec(0, 0, 0), PosVec(0, 1, 0));

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

  glPushMatrix(); // 3D描画
  sphere.Draw();
  cube.Draw();
  {
    glPushMatrix();
    centerCube.Draw();
    glPopMatrix();
  }
  character.Draw();
  glPopMatrix();

  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw(); // 2D描画
}