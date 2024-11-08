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
	baseInit();
	~baseInit();
    _setCallBackFun_ setCallbackFun_ = nullptr;
    GLFWwindow* window = nullptr;
	virtual bool InitGlSource();
    virtual void runDrawProcess() = 0; 
    //void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    virtual void processInput(GLFWwindow* window) = 0;
};


#endif // !BASEINIT_H_
