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

  const std::array<std::string, 27> files{"Isageros Staff","Director\nisssss","Planner\nkkkkkk",
  "Story Writer\nyyyyy","Environment Programming\nisssss","Story Programming\nyyyyy",
  "UI Programming\nisssss\nkkkkkk\njaaaaaa","Programming - Sumo\njaaaaaa",
  "Programming - Soccer\njaaaaaa","Programming - Tabletennis\nisssss",
  "Programming - Archery\nkkkkkk\nisssss\njaaaaaa","Programming - Baseball\njaaaaaa",
  "Programming - Credit\nkkkkkk","Logo Art\nitttt","Character Art\nitttt","Character Design\nitttt",
  "Map Design\nyyyyy","Item Design\nyyyyy","UI Design\nisssss","Character Modelling\nitttt",
  "Map Modelling\nyyyyy","Item Modelling\nyyyyy","Animation\nisssss","Testing\nisssss\njaaaaaa\nkkkkkk\n",
  "Sounds\nkkkkkk","Producer\nisssss","Thank you for Playing!"};

  const std::string folderName = "credit/";
};

}  // namespace Scene