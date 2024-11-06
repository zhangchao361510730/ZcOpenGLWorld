#include"skyBox.h"
#include"mainLoop.h"
#include"cameraTool.h"
#include"animationTool.h"
#include"loadModelTool.h"
#include"shaderLanguage.h"
#include"modelBindAnimation.h"

mainLoop::mainLoop(/* args */) {

}

mainLoop::~mainLoop() {

}

bool mainLoop::InitGlSource() {
	setCallbackFun_ = mainLoop::setCallBackControl;
	baseInit::InitGlSource();
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //
    glEnable(GL_DEPTH_TEST);
    std::string ModelPath_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/anim_model.fs");
    std::string ModelPath_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/anim_model.vs");
    //std::string animationPath = std::string(CMAKE_CURRENT_DIR).append("/modelResource/Flair/Flair.dae");
    std::string animationPath = std::string(CMAKE_CURRENT_DIR).append("/modelResource/test6.fbx");
    
    loadSkyVertices();
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size()*sizeof(float), skyboxVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    camera_ = new cameraTool(glm::vec3(0.0f, 5.0f, 10.0f));
    skyB_ = new skyBox();
    skyB_->setCameraPtr(camera_);
    skyB_->initSkyBox();
    stbi_set_flip_vertically_on_load(true);// load model need 
    modelBindA_ = new modelBindAnimation(animationPath.c_str());
    loadAnimation_ = new loadAnimation(animationPath.c_str(),modelBindA_);
    animationTool_ = new animationTool(loadAnimation_,this);
    shaderModel_ = new ShaderGLSLTool(ModelPath_vs.c_str(),ModelPath_fs.c_str());

    return true;
}

void mainLoop::runDrawProcess() {
    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        m_DeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        animationTool_->UpdateAnimation(m_DeltaTime);
        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderModel_->use();
        glm::mat4 projection = glm::perspective(glm::radians(camera_->Zoom), (float)windowsWidth / (float)windowsHeight, 0.1f, 100.0f);
        glm::mat4 view = camera_->GetViewMatrix();
        shaderModel_->setMat4("projection", projection);
        shaderModel_->setMat4("view", view);
        auto transforms = animationTool_->GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i) {
            shaderModel_->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
        }
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.4f, -15.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        shaderModel_->setMat4("model", model);
        modelBindA_->Draw(*shaderModel_);

        skyB_->runDrawProcess(view,projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    unInitResource();
}

void mainLoop::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mainLoop::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    mainLoop* thiz = (mainLoop*)glfwGetWindowUserPointer(window);
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

void mainLoop::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    mainLoop* thiz = (mainLoop*)glfwGetWindowUserPointer(window);
    thiz->camera_->ProcessMouseScroll(static_cast<float>(yoffset));
}

void mainLoop::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    mainLoop* thiz = (mainLoop*)glfwGetWindowUserPointer(window);
    // if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    //     glfwSetWindowShouldClose(window, true); // 按下 ESC 键关闭窗口
    // }
    
    // if (key == GLFW_KEY_W || action == GLFW_PRESS) {
    //     thiz->camera_->ProcessKeyboard(FORWARD, thiz->m_DeltaTime);
    // }
    // if (key == GLFW_KEY_S || action == GLFW_PRESS) {
    //     thiz->camera_->ProcessKeyboard(BACKWARD, thiz->m_DeltaTime);
    // }
    // if (key == GLFW_KEY_A || action == GLFW_PRESS) {
    //     thiz->camera_->ProcessKeyboard(LEFT, thiz->m_DeltaTime);
    // }
    // if (key == GLFW_KEY_D || action == GLFW_PRESS) {
    //     thiz->camera_->ProcessKeyboard(RIGHT, thiz->m_DeltaTime);
    // }

    if (key == GLFW_KEY_X) {
        if (action == GLFW_PRESS) {
            thiz->isAnimating = true;
        }
        else if (action == GLFW_RELEASE) {
            thiz->isAnimating = false;
            //thiz->m_CurrentTime = 0.0f; // 重置动画时间
        }
    }
}


void mainLoop::setCallBackControl(void*thiz) {
	mainLoop* thiz_ = (mainLoop*)thiz;
    if (thiz_ == nullptr) {
        std::cerr<<__FILE__<<" thiz_ is nullptr"<<std::endl;
        return;
    }
    glfwSetFramebufferSizeCallback(thiz_->window, mainLoop::framebuffer_size_callback);
    glfwSetCursorPosCallback(thiz_->window, mainLoop::mouse_callback);
    glfwSetScrollCallback(thiz_->window, mainLoop::scroll_callback);
    glfwSetKeyCallback(thiz_->window,mainLoop::keyCallback);
    glfwSetInputMode(thiz_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void mainLoop::processInput(GLFWwindow *window) {
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_->ProcessKeyboard(FORWARD, m_DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_->ProcessKeyboard(BACKWARD, m_DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_->ProcessKeyboard(LEFT, m_DeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_->ProcessKeyboard(RIGHT, m_DeltaTime);

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        isAnimating = true;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
        isAnimating = false;
        //m_CurrentTime = 0.0f; // 重置动画时间
    }
}



bool mainLoop::unInitResource() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderModel_->attachId);

    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    glDeleteProgram(shaderSkyBox_->attachId);

    glfwTerminate();
    delete shaderModel_;
    return true;
}