#pragma once
#include<GL/glut.h>

#include "SceneBase.hpp"

#include "ApplicationPreference.hpp"
#include "Camera.hpp"
#include "Color255.hpp"
#include "CubeObject.hpp"
#include "SceneBase.hpp"
#include "SphereObject.hpp"
#include "ConeObject.hpp"
#include "DodecahedronObject.hpp"
#include "IcosahedronObject.hpp"
#include "SphereObject.hpp"
#include "TeapotObject.hpp"
#include "TorusObject.hpp"

namespace ArcheryScene{
	class GameScene: public Scene::SceneBase {
		public:
			//GameScene() {}
			GameScene();
			~GameScene() {}
		
			void Update() override;
        	void Draw() override;
        	void KeyboardProc(unsigned char key, int x, int y) override ;
        	void MouseProc(int button, int state, int x, int y) override {}
        	void MotionProc(int x, int y) override {}
        	void PassiveMotionProc(int x, int y) override {}
        	void SpecialFuncProc(int key, int x, int y) override ;

		private:
  			float deg;
    		Color255 boxAmbient;
  			Obj::Sphere sphere;
  			Obj::Cube cube;
  			Obj::Torus centerCube;
	};
}