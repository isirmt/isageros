#pragma once
#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <array>

#include "jfont.hpp"
#include "2DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneManager.hpp"
#include "SceneBase.hpp"

namespace Scene {
class CreditScene : public SceneBase {
 public:
  CreditScene();
  ~CreditScene() {
    delete background;
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
  Obj::Image* background;

  Obj::Text* text;

  Obj::Rectangle* rect;

  Obj::Button* backButton;

  float TextPosY=0.0;

  int n=0;

  const std::array<std::string, 27> files{{"Isageros Staff","Director\n井筒 ミリ","Planner\nkentos",
  "Story Writer\nゆっけ","Environment Programming\n井筒 ミリ","Story Programming\nゆっけ",
  "UI Programming\n井筒 ミリ\nkentos\nJakoP","Programming - Sumo\nJakoP",
  "Programming - Soccer\nJakoP","Programming - Tabletennis\n井筒 ミリ",
  "Programming - Archery\nkentos\n井筒 ミリ\nJakoP","Programming - Baseball\nJakoP",
  "Programming - Credit\nkentos","Logo Art\nいとろ","Character Art\nいとろ","Character Design\nいとろ",
  "Map Design\nゆっけ","Item Design\nゆっけ","UI Design\n井筒 ミリ","Character Modelling\nいとろ",
  "Map Modelling\nゆっけ","Item Modelling\nゆっけ","Animation\n井筒 ミリ","Testing\n井筒 ミリ\nJakoP\nkentos\n",
  "Sounds\nkentos","Producer\n井筒 ミリ","Thank you for Playing!"}};

  const std::string folderName = "credit/";
};

}  // namespace Scene