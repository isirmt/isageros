#pragma once
#include <GL/glut.h>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"
#include "SceneManager.hpp"

namespace Scene {
class ArcheryScene : public SceneBase {
 public:
  // GameScene() {}
  ArcheryScene();
  ~ArcheryScene() {
    delete backButton;
    delete rect;
    delete text;
  }


  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override {}
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

  private:
    void RuleMode();

 private:
  float deg;
  Color255 boxAmbient;
  Obj::Sphere sphere;
  Obj::Cube cube;
  Obj::ObjFile stage;
  Obj::Cylinder centerCube;
  Obj::ObjFile arrow;
  Obj::ObjFile bow;
  Obj::Text* text;
  Obj::Text* ruleText;
  Obj::Button* backButton; 
  Obj::Button* startButton;
  Obj::Button* ruleButton;
  Obj::Image* nImage;
  Obj::Image* goRect;
  Obj::Image* quotaImage;
  Obj::Image* miniuiImage;
  Obj::Rectangle* ruleBack;
  Obj::Rectangle* textBack;
  Obj::Rectangle* rect;
  Obj::Line* line1;
  Obj::Line* line2;
  bool Mouseflag = false;
  bool isShooting;
  bool flag;
  bool gameStart;
  bool ruleView;
  bool point1;
  bool point2;
  bool point3;
  bool point4;
  bool point5;
  bool point6;
  bool point7;
  bool point8;
  bool point9;
  bool point10;
  float RotX = 0.0;
  float RotY = 0.0;
  float RotZ = 0.0;
  int point = 0;
  int turn = 0;
  int high_point = 0;
  int clearScore = 20;

  const PosVec ruleImageOffset =
      PosVec(ApplicationPreference::windowSize.x / 8.f,
              ApplicationPreference::windowSize.y / 8.f);
  const PosVec ruleImageSize =
      PosVec(ApplicationPreference::windowSize.x * 3.f / 4.f,
          ApplicationPreference::windowSize.y * 3.f / 4.f);
  std::vector<Obj::Image*> rulePics;

  const float timerCountMax = 4.f;
  float timerCount;

  const std::string folderName = "minigames/archery/";
};
}  // namespace Scene