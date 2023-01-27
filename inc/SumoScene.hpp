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
                delete text;
                delete rect;
            }

            void Update() override;
            void Draw() override;
            void KeyboardProc(unsigned char key, int x, int y) override{}
            void MouseProc(int button, int state, int x, int y) override;
            void MotionProc(int x, int y) override {}
            void PassiveMotionProc(int x, int y) override {}
            void SpecialFuncProc(int key, int x, int y) override {}

        private:
            void RuleMode();

        private:
            Color255 boxAmbient;
            Obj::ObjFile stage;
            Obj::ObjFile player;
            Obj::ObjFile enemy;
            Obj::Button* backbutton;
            Obj::Button* startbutton;
            Obj::Button* ruleButton;
            Obj::Text* text;
            Obj::Text* text_2;
            Obj::Text* ruleText;
            Obj::Image* nImage;
            Obj::Image* goRect;
            Obj::Image* quotaImage;
            Obj::Image* miniuiImage;
            Obj::Rectangle* ruleBack;
            Obj::Rectangle* textBack;
            Obj::Rectangle* rect;
            const std::string folderName = "minigames/sumo/";
            bool gamestart;
            bool ruleView;
            float pushPower;
            int clickCount;

            const PosVec ruleImageOffset =
                PosVec(ApplicationPreference::windowSize.x / 8.f,
                        ApplicationPreference::windowSize.y / 8.f);
            const PosVec ruleImageSize =
                PosVec(ApplicationPreference::windowSize.x * 3.f / 4.f,
                    ApplicationPreference::windowSize.y * 3.f / 4.f);
            std::vector<Obj::Image*> rulePics;
    };
}