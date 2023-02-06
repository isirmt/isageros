#pragma once
#include <GL/glut.h>

#include "2DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"
#include "SceneManager.hpp"

namespace Scene {
class SettingScene : public SceneBase {
 public:
  SettingScene();
  ~SettingScene() {
    delete background;
    delete saveStoryResetButton;
    delete saveStoryResetText;
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

  Obj::Button* saveStoryResetButton;
  Obj::Text* saveStoryResetText;

  Obj::Button* backButton;

  const std::string selectFolderName = "select/";
};

}  // namespace Scene