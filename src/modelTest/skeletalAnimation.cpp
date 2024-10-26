#include"skeletalAnimation.h"
#include"commonTool/loadModelTool.h"
#include"commonTool/cameraTool.h"
#include"commonTool/shaderLanguage.h"

skeletalAnimation::skeletalAnimation(/* args */) {

}

skeletalAnimation::~skeletalAnimation() {

}

bool skeletalAnimation::InitGlSource() {
	setCallbackFun_ = skeletalAnimation::setCallBackControl;
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    return true;
}

void skeletalAnimation::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void skeletalAnimation::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    skeletalAnimation* thiz = (skeletalAnimation*)glfwGetWindowUserPointer(window);
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (thiz->firstMouse) {
        thiz->lastX = xpos;
        thiz->lastY = ypos;
        thiz->firstMouse = false;
    }
    float xoffset = xpos - thiz->lastX;
    float yoffset = thiz->lastY - ypos; // reversed since y-coordinates go from bottom to top
    thiz->lastX = xpos;
    thiz->lastY = ypos;
    thiz->camera_->ProcessMouseMovement(xoffset, yoffset);
}

void skeletalAnimation::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    skeletalAnimation* thiz = (skeletalAnimation*)glfwGetWindowUserPointer(window);
    thiz->camera_->ProcessMouseScroll(static_cast<float>(yoffset));
}

void skeletalAnimation::setCallBackControl(void*thiz) {
	skeletalAnimation* thiz_ = (skeletalAnimation*)thiz;
    if (thiz_ == nullptr) {
        std::cerr<<__FILE__<<" thiz_ is nullptr"<<std::endl;
        return;
    }
    glfwSetFramebufferSizeCallback(thiz_->window, skeletalAnimation::framebuffer_size_callback);
    glfwSetCursorPosCallback(thiz_->window, skeletalAnimation::mouse_callback);
    glfwSetScrollCallback(thiz_->window, skeletalAnimation::scroll_callback);
    glfwSetInputMode(thiz_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void skeletalAnimation::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_->ProcessKeyboard(RIGHT, deltaTime);
}

void skeletalAnimation::runDrawProcess() {
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

bool skeletalAnimation::unInitResource() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderTool_->attachId);
    glfwTerminate();
    delete shaderTool_;
    return true;
}
