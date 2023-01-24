#pragma once
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>


#include <iostream>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"
#include "MouseInput.hpp"
#include "SceneManager.hpp"

namespace Scene{
    class SoccerScene : public SceneBase{
        public:
            SoccerScene();
            ~SoccerScene(){
                delete backbutton;
                delete text;
            }

            void Update() override;
            void Draw() override;
            void KeyboardProc(unsigned char key, int x, int y) override{}
            void MouseProc(int button, int state, int x, int y) override{}
            void MotionProc(int x, int y) override{}
            void PassiveMotionProc(int x, int y) override{}
            void SpecialFuncProc(int key, int x, int y) override{}

        private:
            void KeeperPosition(); 
            void threeMouseCondition(bool x);

        private:
            Obj::Button* backbutton;
            Obj::ObjFile player;
            Obj::ObjFile enemy;
            Obj::Text* text;
            Obj::ObjFile stage;
            Obj::Sphere ball;
            Obj::Button* startButton;
            Obj::Button* centerButton;
            Obj::Button* rightButton;
            Obj::Button* leftButton;
            const std::string folderName = "minigames/soccer/";
            int ransu;
            bool gameStart;
    };
}