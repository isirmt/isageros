#pragma once
#include <GL/glut.h>

#include <map>

#include "2DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"
#include "SceneManager.hpp"

namespace Scene {
class GameSelectorScene : public SceneBase {
 public:
  GameSelectorScene();
  ~GameSelectorScene() { delete background; }

  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override {}
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

 private:
  Obj::Image* background;
  Obj::Button* button;

  std::map<std::string, Obj::Image*> gameThumbs;

  const std::string folderName = "select/";
};
}  // namespace Scene