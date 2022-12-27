#include "inc/ArcheryScene.hpp"
#include <stdio.h>

void ArcheryScene::GameScene::Update(){
}

void ArcheryScene::GameScene::Draw(){
    // printf("アーチェリーのゲーム画面\n");
}

void ArcheryScene::GameScene::SpecialFuncProc(int key,int x,int y){
    printf("押された！\n");
}

void ArcheryScene::GameScene::KeyboardProc(unsigned char key, int x, int y){
    printf("推してる\n");
}

namespace ArcheryScene{
    class yumi{
        
    };
}