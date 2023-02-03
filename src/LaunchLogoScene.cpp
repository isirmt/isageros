#include "LaunchLogoScene.hpp"

#include "TitleScene.hpp"

Scene::LaunchLogoScene::LaunchLogoScene() {
  Camera::SetActive(true);
  SceneBase::SetOrthoCameraWindow();
  Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(0, 0, 2500), PosVec(0, 0, 0), PosVec(0, 1, 0));
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  background = new Obj::Rectangle(PosVec(), ApplicationPreference::windowSize);
  background->SetInnerColor(Color255(20));

  PosVec menuButtonSize(500, 75);
  Color255 buttonInnerColor("#40C8C0");
  Color255 buttonOutlineColor(35, 57, 40);
  float buttonOutlineWidth = 2.f;
  PosVec bpos;

  bpos = PosVec(ApplicationPreference::windowSize.x / 4.f,
                (ApplicationPreference::windowSize.y - ApplicationPreference::windowSize.x / 2.f / 17.f * 2.f) / 2.f);
  logo = new Obj::Image(
      bpos,
      PosVec(ApplicationPreference::windowSize.x / 2.f,
             ApplicationPreference::windowSize.x / 2.f / 17.f * 2.f),
      ApplicationPreference::imgFilePath + folderName + "logo.ppm");

  back = new Obj::Image(
      PosVec(ApplicationPreference::windowSize.x / 2.f,
             ApplicationPreference::windowSize.y + 150),
      PosVec(1, 1),
      ApplicationPreference::imgFilePath + folderName + "titleBack.ppm");

  layer2D.AddObject(background);
  layer2D.AddObject(logo);

  timeleft = 2.f;
}

void Scene::LaunchLogoScene::Update() {
  layer2D.Collide();
  timeleft -= Time::DeltaTime();

  if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST) {
    clickCounts++;
  }

  if (clickCounts >= 3 || timeleft <= 0.f) {
    layer2D.DeleteObject(back);
    layer2D.AddObject(back);
    logo->ChangeValueWithAnimation(&logo->GetVectorPointer(VectorType::POS)->x,
                                   ApplicationPreference::windowSize.x / 2.f,
                                   4.f);
    logo->ChangeValueWithAnimation(&logo->GetVectorPointer(VectorType::POS)->y,
                                   -50.f, 4.f);
    logo->ChangeValueWithAnimation(&logo->GetVectorPointer(VectorType::SIZE)->x,
                                   0.f, 4.f);
    logo->ChangeValueWithAnimation(&logo->GetVectorPointer(VectorType::SIZE)->y,
                                   0.f, 4.f);

    background->ChangeColorWithAnimation(background->GetColor(ColorType::INNER),
                                         new Color255("#98DCDF"), .4f);

    back->ChangeValueWithAnimation(&back->GetVectorPointer(VectorType::POS)->x,
                                   0, 10.f);
    back->ChangeValueWithAnimation(&back->GetVectorPointer(VectorType::POS)->y,
                                   0, 10.f);
    back->ChangeValueWithAnimation(&back->GetVectorPointer(VectorType::SIZE)->x,
                                   ApplicationPreference::windowSize.x, 10.f);
    back->ChangeValueWithAnimation(&back->GetVectorPointer(VectorType::SIZE)->y,
                                   ApplicationPreference::windowSize.y, 10.f);

    if (back->GetPos().y < 1.f) {
      SceneManager::ChangeScene(new Scene::TitleScene());
      return;
    }
  } else {
    if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST) {
      logo->SetPos(PosVec(ApplicationPreference::windowSize.x / 4.f - 10.f,
                          (ApplicationPreference::windowSize.y - ApplicationPreference::windowSize.x / 2.f / 17.f * 2.f) / 2.f - 10.f));
      logo->SetSize(PosVec(ApplicationPreference::windowSize.x / 2.f + 20.f,
                           ApplicationPreference::windowSize.x / 2.f / 17.f * 2.f + 20));
      logo->ChangeValueWithAnimation(
          &logo->GetVectorPointer(VectorType::POS)->x, 0, 1.f);
      logo->ChangeValueWithAnimation(
          &logo->GetVectorPointer(VectorType::POS)->y, 0, 1.f);
      logo->ChangeValueWithAnimation(
          &logo->GetVectorPointer(VectorType::SIZE)->x, 0, 1.f);
      logo->ChangeValueWithAnimation(
          &logo->GetVectorPointer(VectorType::SIZE)->y, 0, 1.f);
      logo->ChangeValueWithAnimation(
          &logo->GetVectorPointer(VectorType::POS)->x,
          ApplicationPreference::windowSize.x / 4.f, 1.f);
      logo->ChangeValueWithAnimation(
          &logo->GetVectorPointer(VectorType::POS)->y,
          (ApplicationPreference::windowSize.y - ApplicationPreference::windowSize.x / 2.f / 17.f * 2.f) / 2.f, 1.f);
      logo->ChangeValueWithAnimation(
          &logo->GetVectorPointer(VectorType::SIZE)->x,
          ApplicationPreference::windowSize.x / 2.f, 1.f);
      logo->ChangeValueWithAnimation(
          &logo->GetVectorPointer(VectorType::SIZE)->y,
          ApplicationPreference::windowSize.x / 2.f / 17.f * 2.f, 1.f);
    }
  }

  layer2D.Update();
}

void Scene::LaunchLogoScene::Draw() {
  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}