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
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,   // top left 
        -0.8f,  -0.6f, 0.0f,
        -0.7f,  0.7f, 0.0f   
    };
    uint32_t indices[] = {  // note that we start from 0!
        0, 1, 2,  // first Triangle
        3, 4, 5   // second Triangle
    };
    // 一个绑定顶点两个绑定缓冲
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    return true;
}

void multipleTriangle::runDrawProcess() {
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(r,g,b, 1.0f);
         std::uniform_real_distribution<float> dis(0.0f, 1.0f); // 定义均匀分布范围
        glClear(GL_COLOR_BUFFER_BIT);
        // draw our first triangle
        glUseProgram(shaderProgram);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, dis(gen), dis(gen),dis(gen), a);
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glBindVertexArray(VAO); 
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); 
        // no need to unbind it every time 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    unInitResource();
}

bool multipleTriangle::unInitResource() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return true;
}
