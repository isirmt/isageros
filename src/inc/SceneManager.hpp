#pragma once
#include "SceneBase.hpp"

namespace Scene
{
    class SceneManager
    {
    public:
        static void Update();

        static void ChangeScene(SceneBase* _scene);

    private:
        // write current scene here.
        static SceneBase* currentScene;
    };
}
