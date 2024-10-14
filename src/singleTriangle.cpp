#include<iostream>

#include"globaDefine.h"
#include"singleTriangle.h"

extern const char* fragmentShaderSource;
extern const char* vertexShaderSource; 


singleTriangle::singleTriangle(/* args */)
{
}

singleTriangle::~singleTriangle()
{
}

bool singleTriangle::init() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(windowsWidth, windowsHeight, "jojoOpenGl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, singleTriangle::framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    // 这类似一个函数指针绑定，只不过还强制转化了一下
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return true;    
}

void singleTriangle::runDrawProcess() {
    
}

void singleTriangle::processInput(GLFWwindow *window) {

}

void  singleTriangle::framebuffer_size_callback(GLFWwindow* window, int width, int height) {

}
