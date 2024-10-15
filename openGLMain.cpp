#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#ifdef PLATFORM_UNIX
#include <unistd.h>
#endif // PLATFORM_UNIX
#include <iostream>
#include <random>
#include"src/globaDefine.h"
#include"src/singleTriangle.h"
#include"src/multipleTriangle.h"

int main() {
    singleTriangle sT;
    sT.InitGlSource();
    sT.runDrawProcess();

    return 0;
}

/*
书签记录，每次结束都更新下面的页数
https://learnopengl-cn.github.io/01%20Getting%20started/05%20Shaders/
*/