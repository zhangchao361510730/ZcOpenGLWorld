#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include"globaDefine.h"
#include"mainLoop.h"

int main() {
    mainLoop* bI = new mainLoop(); 
    bI->InitGlSource();
    bI->runDrawProcess();
    delete bI;
    return 0;
}

/*
书签记录，每次结束都更新下面的页数
https://learnopengl-cn.github.io/08%20Guest%20Articles/2020/01%20Skeletal%20Animation/#_1
https://www.mixamo.com/#/?limit=48&page=1&type=Motion%2CMotionPack
*/