#pragma once
#include <GL/glut.h>

#include "2DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneManager.hpp"
#include "SceneBase.hpp"

namespace Scene {
class TitleScene : public SceneBase {
 public:
  TitleScene();
  ~TitleScene() {
    delete background;
    delete tennisButton;
    delete archeryButton;
    delete metaText;
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

  Obj::Button* tennisButton;
  Obj::Button* archeryButton;
  Obj::Button* battingButton;

  Obj::Text* metaText;

  const std::string folderName = "title/";
};

}  // namespace Scene