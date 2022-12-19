#pragma once

namespace Scene
{
    class SceneBase
    {
    public:
        SceneBase() {}
        ~SceneBase() {}

        virtual void Update() = 0;
    };
}
