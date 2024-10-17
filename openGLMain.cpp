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

int main() {
    textureImage sT;
    sT.InitGlSource();
    sT.runDrawProcess();

    return 0;
}

/*
书签记录，每次结束都更新下面的页数
https://learnopengl-cn.github.io/01%20Getting%20started/05%20Shaders/
*/