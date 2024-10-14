#ifndef singleTriangle_H_
#define singleTriangle_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class singleTriangle
{
private:
    float r = 1.0f,g = 0.0f,b = 1.0f,a = 1.0f;
    GLFWwindow* window = nullptr;
    std::mt19937 gen; // 使用梅森旋转算法初始化随机数生成器
    uint32_t shaderProgram;
    uint32_t VBO;
    uint32_t VAO;
public:
    singleTriangle(/* args */);
    ~singleTriangle();

    bool init();
    void runDrawProcess();
    bool unInitResource();
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
};

#endif