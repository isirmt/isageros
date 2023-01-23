#pragma once
#include <GL/glut.h>

#include <cmath>
#include <iostream>

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
    delete image;
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

 private:
  Color255 boxAmbient;
  Obj::ObjFile worldMap;
  Obj::ObjFile player;
  Obj::ObjFile enemy;

  Obj::Sphere ball;

  Obj::Button* backButton;
  Obj::Button* startButton;
  Obj::Rectangle* rect;
  Obj::Text* text;
  Obj::Image* image;

  Obj::Null* null;

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