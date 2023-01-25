#pragma once
#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <random>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "MouseInput.hpp"
#include "SceneBase.hpp"
#include "SceneManager.hpp"

namespace Scene {
class TableTennisScene : public SceneBase {
 public:
  TableTennisScene();
  ~TableTennisScene() {
    delete backButton;
    delete rect;
    delete text;
  }

  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override;
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

 private:
  // 機能分割
  void GameStart();
  void GameOver();

  void SetupCurrentRuleDisplayingMode();

 private:
  Color255 boxAmbient;
  Obj::ObjFile worldMap;
  Obj::ObjFile player;
  Obj::ObjFile rPlayer;
  Obj::ObjFile enemy;
  Obj::ObjFile rEnemy;

  Obj::Sphere ball;

  Obj::Button* backButton;
  Obj::Button* startButton;
  Obj::Rectangle* rect;
  Obj::Text* text;

  Obj::Null* null;

  Obj::Image* miniuiImage;
  Obj::Image* quotaImage;
  Obj::Image* goRect;
  Obj::Rectangle* textBack;
  Obj::Button* ruleButton;

  const PosVec ruleImageOffset =
      PosVec(ApplicationPreference::windowSize.x / 8.f,
             ApplicationPreference::windowSize.y / 8.f);
  const PosVec ruleImageSize =
      PosVec(ApplicationPreference::windowSize.x * 3.f / 4.f,
             ApplicationPreference::windowSize.y * 3.f / 4.f);

  bool isShowingRule;
  Obj::Image* nowRule;
  std::vector<Obj::Image*> rulePics;
  Obj::Rectangle* ruleBack;
  Obj::Text* ruleText;

  bool isGameStart;
  bool isPlayerTurn;

  const PosVec stageEndAbs = PosVec(80, 80, 60);
  const float canHitXstart = 60;
  const float canHitXend = 105;

  int playerHitBall;

  const float splitXPos = 0;

  const float groundLevel = 80;

  const float paramG = 350;
  const float paramE = 1;

  const int quotaScore = 10;

  float waitingCameraDeg;

  const std::string folderName = "minigames/tabletennis/";
};

}  // namespace Scene
