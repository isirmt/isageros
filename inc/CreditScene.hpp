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
    delete rect;
    delete backButton;
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

  const std::array<std::string, 28> files{{
    "                Isageros Staff",
    "              Director:井筒 ミリ",
    "                Planner:kentos",
    "              Story Writer:ゆっけ",
    "       Environment Programming:井筒 ミリ",
    "           Story Programming:ゆっけ",
    "   UI Programming:井筒 ミリ・kentos・JakoP",
    "           Programming - Sumo:JakoP",
    "          Programming - Soccer:JakoP",
    "      Programming - Tabletennis:井筒 ミリ",
    "Programming - Archery:kentos・井筒 ミリ・JakoP",
    "    Programming - Baseball:JakoP・井筒 ミリ",
    "          Programming - Credit:kentos",
    "                Logo Art:いとろ",
    "             Character Art:いとろ",
    "            Character Design:いとろ",
    "               Map Design:ゆっけ",
    "              Item Design:ゆっけ",
    "              UI Design:井筒 ミリ",
    "          Character Modelling:いとろ",
    "             Map Modelling:ゆっけ",
    "             Item Modelling:ゆっけ",
    "              Animation:井筒 ミリ",
    "       Testing:井筒 ミリ・JakoP・kentos",
    "                 Sounds:kentos",
    "              Producer:井筒 ミリ",
    "                 Made by TeamH",
    "            Thank you for Playing!"}};

  const std::string folderName = "credit/";
};

}  // namespace Scene