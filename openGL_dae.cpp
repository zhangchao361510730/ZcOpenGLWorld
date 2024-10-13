#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#ifdef PLATFORM_UNIX
#include <unistd.h>
#endif // PLATFORM_UNIX
#include <iostream>

/*
书签记录，每次结束都更新下面的页数
https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/ 
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float r = 1.0f,g = 0.0f,b = 1.0f;
int main()
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



    GLFWwindow* window = glfwCreateWindow(800, 600, "jojoOpenGl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    // 这类似一个函数指针绑定，只不过还强制转化了一下
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glViewport(0, 0, 800, 600);

    //glfwSetKeyCallback(window,) typedef void (* GLFWkeyfun)(GLFWwindow*,int,int,int,int);


    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 通过鼠标改变窗口大小时会，触发这个函数
    glViewport(0, 0, width, height);
    r-=0.1f;
    b-=0.1f;
    if (r <=0.0f || b <=0.0f) {
        r = 1.0f;
        b = 1.0f;
    }
    g=1.0f-r-b;
}