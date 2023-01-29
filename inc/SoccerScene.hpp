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
					 delete rect;
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
				void RuleMode();

        private:
            Obj::Button* backbutton;
            Obj::ObjFile player;
            Obj::ObjFile enemy;
            Obj::Text* text;
            Obj::Text* text_2;
			Obj::Text* ruleText;
            Obj::Null* null;
            Obj::ObjFile stage;
            Obj::Sphere ball;
            Obj::Button* startButton;
            Obj::Button* centerButton;
            Obj::Button* rightButton;
            Obj::Button* leftButton;
			Obj::Button* ruleButton;
            Obj::Image* nImage;
            Obj::Image* goRect;
            Obj::Image* quotaImage;
            Obj::Image* miniuiImage;
            Obj::Rectangle* ruleBack;
            Obj::Rectangle* textBack;
            Obj::Rectangle* rect;
            const std::string folderName = "minigames/soccer/";
            int ransu;
            int point;
            int shootCount;
            bool gameStart;
			bool ruleView;
            float goTimer;
            const float goTimerMax = 5.f;
            float watchingCameraDeg;
            bool cameraFlag;

			const PosVec ruleImageOffset =
                PosVec(ApplicationPreference::windowSize.x / 8.f,
                    ApplicationPreference::windowSize.y / 8.f);
            const PosVec ruleImageSize =
                PosVec(ApplicationPreference::windowSize.x * 3.f / 4.f,
                    ApplicationPreference::windowSize.y * 3.f / 4.f);
            std::vector<Obj::Image*> rulePics;
    };
}