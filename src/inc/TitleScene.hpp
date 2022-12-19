#pragma once
#include "SceneBase.hpp"

namespace Scene
{
    class TitleScene
        : public SceneBase
    {
    public:
        TitleScene() {}
        ~TitleScene() {}

        void Update() override;
    };
}