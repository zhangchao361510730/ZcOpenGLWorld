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
https://www.mixamo.com/#/?limit=48&page=1&type=Motion%2CMotionPack
*/
