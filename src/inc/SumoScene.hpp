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

namespace Scene{
    class SumoScene : public SceneBase{
        public:
            SumoScene();
            ~SumoScene(){
                delete backbutton;
            }

            void Update() override;
            void Draw() override;
            void KeyboardProc(unsigned char key, int x, int y) override{}
            void MouseProc(int button, int state, int x, int y) override;
            void MotionProc(int x, int y) override {}
            void PassiveMotionProc(int x, int y) override {}
            void SpecialFuncProc(int key, int x, int y) override {}

        private:
            Color255 boxAmbient;
            Obj::ObjFile stage;
            Obj::Button* backbutton;
            const std::string folderName = "";
    };
}