
#include<iostream>

#include"globaDefine.h"
#include"singleTriangle.h"

extern const char* fragmentShaderSource;
extern const char* vertexShaderSource; 


singleTriangle::singleTriangle(){

}

singleTriangle::~singleTriangle() {

}

bool singleTriangle::InitGlSource() {
    baseInit::InitGlSource();
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // 左边的-0.5, 0.5
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    // 几个概念: 顶点对象,顶点缓冲区,顶点属性

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 将顶点数据传递给 GPU。这一步将 vertices 数组中的数据复制到当前绑定的缓冲区（即 VBO）
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    return true;    
}

void singleTriangle::runDrawProcess() {
    while(!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);// 使用刚才开发好的着色器程序
        glBindVertexArray(VAO); 
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    unInitResource();
}

bool singleTriangle::unInitResource() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return true;
}
