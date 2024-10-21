#ifndef BASEINIT_H_
#define BASEINIT_H_

#include <random>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"globaDefine.h"

class ShaderGLSLTool;

class baseInit {
public:
    float r = 1.0f, g = 0.0f, b = 1.0f, a = 1.0f;
    GLFWwindow* window = nullptr;
    std::mt19937 gen; // ʹ��÷ɭ��ת�㷨��ʼ�������������
    uint32_t VBO = 0;
    uint32_t VAO = 0;
    ShaderGLSLTool* shaderTool_;

	baseInit();
	~baseInit();

	virtual bool InitGlSource();
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);
};


#endif // !BASEINIT_H_
