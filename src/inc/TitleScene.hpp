#pragma once
#include "SceneBase.hpp"
#include <GL/glut.h>

namespace Scene
{
    class TitleScene
        : public SceneBase
    {
    public:
        TitleScene() {deg = 0.f;}
        ~TitleScene() {}

        void Update() override;
        void Draw() override;
        void KeyboardProc(unsigned char key, int x, int y) override {}
        void MouseProc(int button, int state, int x, int y) override {}
        void MotionProc(int x, int y) override {}
        void PassiveMotionProc(int x, int y) override {}
        void SpecialFuncProc(int key, int x, int y) override {}
        private:
        float deg;
    };
}