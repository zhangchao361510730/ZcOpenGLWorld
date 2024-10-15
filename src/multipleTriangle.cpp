#include"multipleTriangle.h"
extern const char* fragmentShaderSource;
extern const char* vertexShaderSource; 

multipleTriangle::multipleTriangle(/* args */) {

}

multipleTriangle::~multipleTriangle() {

}

bool multipleTriangle::InitGlSource() {
    baseInit::InitGlSource();
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    uint32_t indices[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    return true;

    
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void multipleTriangle::runDrawProcess() {
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    unInitResource();
}

bool multipleTriangle::unInitResource() {
    
    return true;
}
