#include "CreditScene.hpp"

#include "TitleScene.hpp"

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
  
  Color255 buttonInnerColor("#40C8C0");
  buttonInnerColor = Color255(255, 100, 50);
  backButton = new Obj::Button(Obj::Object2DAnchor::AnchorLowerRight(PosVec(30+50, 30)), PosVec(50, 50), true, true);
  backButton->SetInnerColor(buttonInnerColor, buttonInnerColor * 0.8,
                            buttonInnerColor * 0.65, buttonInnerColor * 0.75);
  backButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
  backButton->SetInnerAnimation(.2f);

  rect = new Obj::Rectangle(PosVec(0, 0),
                         PosVec(ApplicationPreference::windowSize.x/2,
                         ApplicationPreference::windowSize.y));
  rect->SetInnerColor(Color255(0, 0, 0));

  text = new Obj::Text(PosVec(ApplicationPreference::windowSize.x/10, -5.0),PosVec(),
                       "                Isageros Staff");
  text->SetInnerColor(Color255(255, 255, 255));


  LightManager::Set(GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
                    Color255(1.f, 1.f, 1.f, 1.0f),
                    Color255(0.0f, 0.0f, 0.0f, 1.f));

  layer2D.AddObject(background);
  layer2D.AddObject(rect);
  layer2D.AddObject(text);
  layer2D.AddObject(backButton);
}

void Scene::CreditScene::Update() {
    layer2D.Collide();
    
    TextPosY += 200.0 * Time::DeltaTime();
    text->SetPos(PosVec(ApplicationPreference::windowSize.x/10,TextPosY));

    if(TextPosY >= ApplicationPreference::windowSize.y){
        n++;
        TextPosY = -5.0;
        if(n>=27){
            SceneManager::ChangeScene(new TitleScene());
            return;
        }else{
            text->SetString(files[n]);
        }
    }

    if (backButton->GetMouseSelected()) {
        backButton->SetMouseOff();
        SceneManager::ChangeScene(new TitleScene());
        return;
    }

    layer2D.Update();
}

void Scene::CreditScene::Draw() {
  SceneBase::Set3DDrawMode();
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw();  // 2D描画
}