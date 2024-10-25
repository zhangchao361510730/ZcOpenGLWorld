#include"modelShow.h"
#include"commonTool/loadModelTool.h"
#include"commonTool/cameraTool.h"
#include"commonTool/shaderLanguage.h"

modelShow::modelShow(/* args */) {

}

modelShow::~modelShow() {

}

void modelShow::setCallBackControl(void*) {

}

bool modelShow::InitGlSource() {
	setCallbackFun_ = modelShow::setCallBackControl;
	baseInit::InitGlSource();
    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    std::string path_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/shader.fs");
    std::string path_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/shader.vs");
    std::string path_model1 = std::string(CMAKE_CURRENT_DIR).append("/modelResource/nanosuit/nanosuit.obj");

    // build and compile our shader zprogram
    ShaderGLSLTool_ = new ShaderGLSLTool(path_vs.c_str(),path_fs.c_str());
    camera_ = new cameraTool(glm::vec3(0.0f, 0.0f, 3.0f));
    meshTool_ = new loadModelTool(path_model1.c_str());

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    return true;
}

void modelShow::runDrawProcess() {
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(r,g,b, 1.0f);
         std::uniform_real_distribution<float> dis(0.0f, 1.0f); // 定义均匀分布范围
        glClear(GL_COLOR_BUFFER_BIT);
        // draw our first triangle
        glUseProgram(shaderTool_->attachId);
        int vertexColorLocation = glGetUniformLocation(shaderTool_->attachId, "ourColor");
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

bool modelShow::unInitResource() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderTool_->attachId);
    glfwTerminate();
    delete shaderTool_;
    return true;
}
