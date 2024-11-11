#ifndef H_reflectionBox_H
#define H_reflectionBox_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include"shaderLanguage.h"
#include"cameraTool.h"

class reflectionBox
{
private:
    /* data */
    std::vector<float>cubeVertices;
    uint32_t cubeVAO, cubeVBO;
    ShaderGLSLTool*shaderReflectionBox_; 
    cameraTool* camera;
    
    std::vector<glm::vec3> MultiDrawPositions;
public:
    uint32_t cubemapTexture;
    bool InitReflectionBox();
    reflectionBox(/* args */);
    void loadVertices();
    ~reflectionBox();
    void setCameraPtr(cameraTool* camera_);
    void runDrawProcess(glm::mat4 &model,glm::mat4 &view,glm::mat4 &projection);
};

#endif