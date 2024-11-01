#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <random>

#ifdef PLATFORM_UNIX
#include <unistd.h>
#endif

#include"src/globaDefine.h"
#include"singleTriangle.h"
#include"modelShow.h"
#include"textureImage.h"
#include"cameraControl.h"
#include"lightControl.h"
#include"skeletalAnimation.h"

int main() {
    baseInit* bI = new skeletalAnimation(); 
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