#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <random>

#ifdef PLATFORM_UNIX
#include <unistd.h>
#endif

#include"src/globaDefine.h"
#include"src/singleTriangle.h"
#include"src/multipleTriangle.h"
#include"src/textureImage.h"
#include"src/cameraControl.h"
#include"src/lightControl.h"

int main() {

    baseInit* bI = new lightControl(); 
    bI->InitGlSource();
    bI->runDrawProcess();

    return 0;
}

/*
书签记录，每次结束都更新下面的页数
https://learnopengl-cn.github.io/02%20Lighting/06%20Multiple%20lights/
*/