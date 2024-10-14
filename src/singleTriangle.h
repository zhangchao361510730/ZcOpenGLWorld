#ifndef singleTriangle_H_
#define singleTriangle_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class singleTriangle
{
private:
    float r = 1.0f,g = 0.0f,b = 1.0f,a = 1.0f;
public:
    singleTriangle(/* args */);
    ~singleTriangle();

    bool init();
    void runDrawProcess();

    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
};

#endif