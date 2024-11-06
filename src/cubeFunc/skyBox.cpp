#include"skyBox.h"
#include<string>
skyBox::skyBox(/* args */)
{
}

skyBox::~skyBox()
{
}

bool skyBox::initSkyBox() {
    std::string SkyBoxPath_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/skybox.fs");
    std::string SkyBoxPath_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/skybox.vs");
}