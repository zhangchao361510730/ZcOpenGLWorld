#ifndef H_skyBox_H
#define H_skyBox_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include"shaderLanguage.h"
#include"cameraTool.h"

class skyBox {
private:
    ShaderGLSLTool*shaderSkyBox_;
    cameraTool* camera_;
    uint32_t skyboxVAO;
    uint32_t cubemapTexture;
public:
    skyBox();
    bool initSkyBox();
    void runDrawProcess(glm::mat4 &view,glm::mat4 &projection);
    uint32_t loadCubemap(std::vector<std::string> &faces);
    ~skyBox();

};


#endif