#include "CreditScene.hpp"



Scene::CreditScene::CreditScene() {
  Camera::SetActive(true);
  SceneBase::SetOrthoCameraWindow();
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  background = new Obj::Image(
      PosVec(), ApplicationPreference::windowSize,
      ApplicationPreference::imgFilePath + folderName + "titleBack.ppm");

  text = new Obj::Text(PosVec(ApplicationPreference::windowSize.x/2, ApplicationPreference::windowSize.y/2),PosVec(5,5,5),
                       "Isageros Staff");
  text->SetInnerColor(Color255(0, 0, 0));


  LightManager::Set(GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
                    Color255(1.f, 1.f, 1.f, 1.0f),
                    Color255(0.0f, 0.0f, 0.0f, 1.f));

  layer2D.AddObject(background);

}

void Scene::CreditScene::Update() {
  layer2D.Collide();

  layer2D.Update();
}

void Scene::CreditScene::Draw() {
  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}