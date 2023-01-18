#pragma once
#include <GL/glut.h>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"

namespace Scene{
    class BattingScene : public SceneBase {
        public:
            TitleScene();
            ~TitleScene(){
                delete button;
                delete rect;
                delete text;
                delete image;
            }

            void Update() override;
            void Draw() override;
            void KeyboardProc(unsigned char key, int x, int y) override{}
            void MouseProc(int button, int state, int x, int y) override{}
            void MotionProc(int x, int y) override{}
            void PassiveMotionProc(int x, int y) override{}
            void SpecialFuncProc(int key, int x, int y) override{}

        private:
            const std::string floderName = ""
    };
}