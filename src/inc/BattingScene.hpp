#pragma once
#include <GL/glut.h>

#include <iostream>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"
#include "MouseInput.hpp"
#include "SceneManager.hpp"

namespace Scene{
    class BattingScene : public SceneBase {
        public:
            BattingScene();
            ~BattingScene(){
                delete backButton;
                // delete rect;
                delete text;
                delete text_2;
                delete text_3;
                // delete image;
            }

            void Update() override;
            void Draw() override;
            void KeyboardProc(unsigned char key, int x, int y) override{}
            void MouseProc(int button, int state, int x, int y) override{}
            void MotionProc(int x, int y) override{}
            void PassiveMotionProc(int x, int y) override{}
            void SpecialFuncProc(int key, int x, int y) override{}

        private:
            Obj::ObjFile stage;
            Obj::Cylinder bat; 
            Obj::ObjFile player;
            Obj::Sphere ball;
            Obj::ObjFile enemy;
            Obj::Text* text;
            Obj::Text* text_2;
            Obj::Text* text_3;
            Obj::Button* backButton; 
            Obj::Button* startButton;
            const std::string folderName = "minigames/baseball/";
            bool flag;
            bool gameStart;
            int point = 0;
            int strike = 0;
            int high_point = 0;
            int clearScore = 10;
    };
}