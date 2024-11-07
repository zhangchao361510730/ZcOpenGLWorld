#ifndef BUTTON2D_H_
#define BUTTON2D_H_

#include<vector>
#include<string>
#include"shaderLanguage.h"

class button2D {
private:
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    ShaderGLSLTool * shaderSkyBox_;
    uint32_t VAO,VBO,EBO;
public:
    bool InitButton2D();
    void loadVertices();
    void runDrawProcess();
    button2D(/* args */);
    ~button2D();
};





#endif