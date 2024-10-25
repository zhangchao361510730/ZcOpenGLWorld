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
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    std::string path_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/model_loading.fs");
    std::string path_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/model_loading.vs");
    std::string path_model1 = std::string(CMAKE_CURRENT_DIR).append("/modelResource/nanosuit/nanosuit.obj");
    // build and compile our shader zprogram
    shaderTool_ = new ShaderGLSLTool(path_vs.c_str(),path_fs.c_str());
    camera_ = new cameraTool(glm::vec3(0.0f, 0.0f, 3.0f));
    loadModelTool_ = new loadModelTool(path_model1.c_str());
    return true;
}

void modelShow::runDrawProcess() {
    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        processInput(window);
        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // don't forget to enable shader before setting uniforms
        shaderTool_->use();
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera_->Zoom), (float)windowsWidth / (float)windowsHeight, 0.1f, 100.0f);
        glm::mat4 view = camera_->GetViewMatrix();
        shaderTool_->setMat4("projection", projection);
        shaderTool_->setMat4("view", view);
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shaderTool_->setMat4("model", model);
        loadModelTool_->runDrawProcess(*shaderTool_);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
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
