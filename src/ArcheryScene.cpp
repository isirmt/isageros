#include "ArcheryScene.hpp"
#include "TitleScene.hpp"
#include <stdio.h>

Scene::ArcheryScene::ArcheryScene(){
    // Scean::Camera::SetActive(true);
    // Scean::Camera::SetAsPerspective(
    //   ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
    //   70, 0, 100, PosVec(-250, 100, 1000), PosVec(), PosVec(0, 1, 0));
    Camera::SetActive(true);
  	SceneBase::SetOrthoCameraWindow();
  	Camera::SetAsPerspective(
      ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
      30, 1, 99999, PosVec(1000.0, 200.0, 0.0), centerCube.GetPosition(), PosVec(0,1,0));
  	Camera::SetPerspectiveMode(true);
  	Camera::UpdateCamera();
    deg = 90.f;
    arrow = Obj::ObjFile(PosVec(948.0, 195.0, -8.0), PosVec(),
                       PosVec(),ApplicationPreference::modelFilePath + folderName +
                                "archery_arrow.obj");
    arrow.SetShininess(20);
    arrow.SetScale(PosVec(3, 1, 1));
    
    bow = Obj::ObjFile(PosVec(967.0, 195.0, -9.0), PosVec(),
                       PosVec(),ApplicationPreference::modelFilePath + folderName +
                                "archery_bow.obj");
    bow.SetShininess(20);
    bow.SetScale(PosVec(1, 2, 1));

    cube = Obj::Cube(PosVec(-40.0, 10., 0.0), PosVec(500, 7, 0.0),
                   PosVec(0, -300, 0.0));
    cube.SetAmbient(Color255(100, 75, 80));
    cube.SetDiffuse(Color255(.3f, .3f, .3f));
    cube.SetSpecular(Color255(255, 255, 255, 255));
    cube.SetScale(PosVec(10, 10, 10));
    cube.SetShininess(20);
    cube.SetRotate(30, PosVec(.5, .7, 0));

    centerCube = Obj::Cylinder(PosVec(-1000.0, 150.0, 0.0), PosVec(), PosVec());
    centerCube.SetAmbient(Color255(114, 235, 209));
    centerCube.SetDiffuse(Color255(.3f, .3f, .3f));
    centerCube.SetSpecular(Color255(1.f, 1.f, 1.f, 1.f));
    centerCube.SetScale(PosVec(10, 10, 10));
    centerCube.SetShininess(20);
    centerCube.SetRotate(90, PosVec(0, 0, 1));

    stage = Obj::ObjFile(PosVec(0.0, 0.0, 0.0), PosVec(), PosVec(),
                            ApplicationPreference::modelFilePath + folderName +
                                "archery_stage.obj");
    stage.SetScale(PosVec(100, 100, 100));
    stage.SetShininess(20);
    stage.SetRotate(90, PosVec(0, 0, 0));

    Scene::LightManager::Set(
      GL_LIGHT0, PosVec(0, 500, 0), Color255(0.5, 0.5, 0.5, 1.f),
      Color255(1.f, 1.f, 1.f, 1.0f), Color255(0.0f, 0.0f, 0.0f, 1.f));

    Color255 innerCol;
    innerCol = Color255(255, 100, 50);
    backbutton = new Obj::Button(PosVec(30, 30), PosVec(150, 100), true, true);
    backbutton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backbutton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backbutton->SetInnerAnimation(.2f);

    layer2D.AddObject(backbutton);
}

void Scene::ArcheryScene::Update(){
    
    //arrow.SetRotate(90, PosVec(0,0,1));
    
    
    
    PosVec ends[4] = {
    	PosVec(-1000.0, 300.0, 600.0),
    	PosVec(-1000.0, 300.0, -600.0),
    	PosVec(-1000.0,   0.0, -600.0),
    	PosVec(-1000.0,   0.0, 600.0)};
    	
    	bool Mouseflag;
    
    if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) >= PressFrame::FIRST) {
    	Mouseflag = true;
    	Camera::SetAsPerspective(
       ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
       10, 1, 99999, PosVec(1000.0, 200.0, 0.0), PosVec(centerCube.GetPosition().x,(Input::MouseInput::GetMouse().y/ApplicationPreference::windowSize.y)*ends[0].y,(((Input::MouseInput::GetMouse().x/ApplicationPreference::windowSize.x)*ends[1].z*2)-ends[1].z)), PosVec(0,1,0));
      //Camera::SetAsPerspective(
       //ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
       //30, 1, 99999, PosVec(250.0, 200.0, 0.0), centerCube.GetPosition(), PosVec(0,1,0));
    	Camera::UpdateCamera();
    	printf("%f,%f\n",Input::MouseInput::GetMouse().x,Input::MouseInput::GetMouse().y);
    }
    else if(Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::ZERO && Mouseflag == true ){
    	deg -= 1 * Time::DeltaTime();
    	if (deg > 360) deg -= 360;
    	arrow.SetPosition(arrow.GetPosition());
    	arrow.SetVelocity(PosVec(-1000.0, 0.0, 0.0));
    	arrow.SetAcceleration(PosVec(0.0, -1500.0, 0.0));
			arrow.SetRotate(deg, PosVec(1,0,0));
    	Camera::SetAsPerspective(
       ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
       30, 1, 99999, PosVec(arrow.GetPosition().x+30,arrow.GetPosition().y+1,arrow.GetPosition().z+1), arrow.GetPosition(), PosVec(0,1,0));
      Camera::UpdateCamera();
      printf("%f,%f,%f\n",arrow.GetPosition().x,arrow.GetPosition().y,arrow.GetPosition().z);
    }else{
      Camera::SetAsPerspective(
       ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
       30, 1, 99999, PosVec(1000.0, 200.0, 0.0), centerCube.GetPosition(), PosVec(0,1,0));
      Camera::UpdateCamera();
    }
    
    arrow.Update();
    //cube.Update();
    centerCube.Update();
    stage.Update();
    bow.Update();

    layer2D.Collide();

    if (backbutton->GetMouseSelected()) {
        backbutton->SetMouseOff();
        SceneManager::ChangeScene(new TitleScene());
        return;
    }

    layer2D.Update();
   
}

void Scene::ArcheryScene::Draw(){
		SceneBase::Set3DDrawMode();
  Camera::SetPerspectiveMode(true);
  Camera::UpdateCamera();

  glPushMatrix(); // 3D描画
  {
    glPushMatrix();
    glRotatef(90, 0,0,0);
    arrow.Draw();
    glPopMatrix();
  }
  arrow.Draw();
  bow.Draw();
  //cube.Draw();
  stage.Draw();
  {
    glPushMatrix();
    centerCube.Draw();
    glPopMatrix();
  }
  //character.Draw();
  glPopMatrix();

  SceneBase::Set2DDrawMode();
  Camera::SetPerspectiveMode(false);
  Camera::UpdateCamera();

  layer2D.Draw(); // 2D描画
}

// void Scene::ArcheryScene::MouseProc(int button, int state, int x, int y) {}

// void Scene::ArcheryScene::SpecialFuncProc(int key,int x,int y){
//     printf("押された！\n");
// }

// void Scene::ArcheryScene::KeyboardProc(unsigned char key, int x, int y){
//     switch (key){
//         case 'x':
//             printf("推してる\n");
//             break;
//         case 'y':
//             printf("推してる?\n");
//             break;
//     }
//     //printf("推してる\n");
// }