#ifndef BUTTON2D_H_
#define BUTTON2D_H_

#include<vector>
#include<string>
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include"shaderLanguage.h"

class button2D {
private:
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    ShaderGLSLTool * shaderSkyBox_;
    uint32_t VAO,VBO,EBO;
    void loadVertices();
public:
    bool InitButton2D();
    void runDrawProcess();
    button2D(/* args */);
    ~button2D();
};





#endif