#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"globaDefine.h"
// 顶点数据：按钮的四个角
float vertices[] = {
    // 位置              // 颜色
    0.0f, 0.0f,          0.2f, 0.6f, 0.8f,  // 左下角
    1.0f, 0.0f,          0.2f, 0.6f, 0.8f,  // 右下角
    1.0f, 1.0f,          0.2f, 0.6f, 0.8f,  // 右上角
    0.0f, 1.0f,          0.2f, 0.6f, 0.8f   // 左上角
};

// 索引数组，指定顶点顺序
unsigned int indices[] = {
    0, 1, 2, // 第一个三角形
    0, 2, 3  // 第二个三角形
};

// 设置一个矩阵和着色器
GLuint VAO, VBO, EBO, shaderProgram;

void setupShader() {
    // 创建并编译着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // (着色器加载、编译代码省略)
    
    // 链接着色器程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
}

void drawButton() {
    // 使用着色器程序
    glUseProgram(shaderProgram);
    
    // 设置正交投影
    glm::mat4 projection = glm::ortho(0.0f, (float)windowsWidth, (float)windowsHeight, 0.0f);
    GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // 创建 VAO 和 VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 绘制按钮
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制按钮
    drawButton();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}
