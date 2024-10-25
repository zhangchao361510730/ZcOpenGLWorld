#ifndef BASEINIT_H_
#define BASEINIT_H_

#include <random>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"globaDefine.h"


class ShaderGLSLTool;

typedef void(*_setCallBackFun_)(void*);

class baseInit {
public:
    float r = 1.0f, g = 0.0f, b = 1.0f, a = 1.0f;
    GLFWwindow* window = nullptr;
    std::mt19937 gen; 
    uint32_t VBO = 0;
    uint32_t VAO = 0;
    ShaderGLSLTool* shaderTool_;

	baseInit();
	~baseInit();
    _setCallBackFun_ setCallbackFun_ = nullptr;

	virtual bool InitGlSource();
    virtual void runDrawProcess() = 0; 
    //void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    virtual void processInput(GLFWwindow* window) = 0;
};


#endif // !BASEINIT_H_
