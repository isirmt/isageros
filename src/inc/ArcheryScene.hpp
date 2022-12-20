#pragma once

#include "SceneBase.hpp"

namespace ArcheryScene{
	class GameScene
		: public Scene::SceneBase {
	public:
		GameScene() {}
		~GameScene() {}
		
		void Update() override;
        void Draw() override;
        void KeyboardProc(unsigned char key, int x, int y) override ;
        void MouseProc(int button, int state, int x, int y) override {}
        void MotionProc(int x, int y) override {}
        void PassiveMotionProc(int x, int y) override {}
        void SpecialFuncProc(int key, int x, int y) override ;
		};
}