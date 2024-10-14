#ifndef BASEINIT_H_
#define BASEINIT_H_

#include <random>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class baseInit {
public:
    float r = 1.0f, g = 0.0f, b = 1.0f, a = 1.0f;
    GLFWwindow* window = nullptr;
    std::mt19937 gen; // 使用梅森旋转算法初始化随机数生成器
    uint32_t shaderProgram = 0;
    uint32_t VBO = 0;
    uint32_t VAO = 0;

	baseInit();
	~baseInit();

	virtual bool InitGlSource();
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);
};


#endif // !BASEINIT_H_
