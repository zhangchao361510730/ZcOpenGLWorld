#include"animationScene.h"
#include"skyBox.h"
#include"animationScene.h"
#include"cameraTool.h"
#include"button2D.h"
#include"reflectionBox.h"
#include"animationTool.h"
#include"loadModelTool.h"
#include"shaderLanguage.h"
#include"modelBindAnimation.h"

animationScene::animationScene(GLFWwindow* windows_):Scene(windows_)
{
}

animationScene::~animationScene()
{
}

void animationScene::glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}


void animationScene::Init() {
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    glfwSetWindowUserPointer(window, (void*)this);
    setCallBackControl(this);
    glEnable(GL_DEPTH_TEST);
    std::string ModelPath_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/anim_model.fs");
    std::string ModelPath_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/anim_model.vs");
    std::string animationPath = std::string(CMAKE_CURRENT_DIR).append("/modelResource/test6.fbx");

    button2D_ = new button2D();
    button2D_->setGLFWwindow(window);
    button2D_->InitButton2D();
    //glm::mat4 projection = glm::ortho(0.0f, (float)windowsWidth, (float)windowsHeight, 0.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    camera_ = new cameraTool(glm::vec3(0.0f, 5.0f, 10.0f));
    skyB_ = new skyBox();
    skyB_->setCameraPtr(camera_);
    skyB_->initSkyBox();// cubemapTexture

    reflectionBox_ = new reflectionBox();
    reflectionBox_->setCameraPtr(camera_);
    reflectionBox_->cubemapTexture = skyB_->cubemapTexture;
    reflectionBox_->InitReflectionBox();

    stbi_set_flip_vertically_on_load(true);// load model need 
    modelBindA_ = new modelBindAnimation(animationPath.c_str());
    loadAnimation_ = new loadAnimation(animationPath.c_str(),modelBindA_);
    animationTool_ = new animationTool(loadAnimation_,this);
    shaderModel_ = new ShaderGLSLTool(ModelPath_vs.c_str(),ModelPath_fs.c_str());
    hasInit = true;
}

void animationScene::Update(float dt) {
        isAnimating = button2D_->flag;
        m_DeltaTime = dt - lastFrame;
        lastFrame = dt;

        processInput(window);
        animationTool_->UpdateAnimation(m_DeltaTime);
}

void animationScene::setSceneManager(SceneManager * _SceneManager_) {
        SceneManager_ = _SceneManager_;
}


void animationScene::Render() {
        button2D_->runDrawProcess();
        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderModel_->use();
        glm::mat4 projection = glm::perspective(glm::radians(camera_->Zoom), (float)windowsWidth / (float)windowsHeight, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(0.0f, (float)windowsWidth, (float)windowsHeight, 0.0f);

        glm::mat4 view = camera_->GetViewMatrix();
        shaderModel_->setMat4("projection", projection);
        shaderModel_->setMat4("view", view);
        auto transforms = animationTool_->GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i) {
            shaderModel_->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
        }


    // 位置数组，定义每个模型的位置
    // std::vector<glm::vec3> modelPositions = {
    //     glm::vec3(0.0f, -0.4f, -15.0f),
    //     glm::vec3(2.0f, -0.4f, -15.0f),
    //     glm::vec3(-2.0f, -0.4f, -15.0f)
    // };

    // // 渲染每个位置的模型
    // for (const auto& pos : modelPositions) {
    //     glm::mat4 model = glm::mat4(1.0f);
    //     model = glm::translate(model, pos); // 设置位置
    //     model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f)); // 缩放
    //     shaderModel_->setMat4("model", model);
    //     modelBindA_->Draw(*shaderModel_);
    // }

        // // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.4f, -15.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        shaderModel_->setMat4("model", model);
        modelBindA_->Draw(*shaderModel_);

//         glm::mat4 model2 = glm::mat4(1.0f);
//         model2 = glm::translate(model2, glm::vec3(0.0f, -4.0f, -16.0f));  // 平移 y + 向上   z - 向前
 #define scValue 6.0f
//         model2 = glm::scale(model2, glm::vec3(scValue, scValue, scValue));      // 缩放
//         reflectionBox_->runDrawProcess(model2,view,projection);

    std::vector<glm::mat4> models = {
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),  // 第一个盒子的位置
        glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f)),  // 第二个盒子的位置
        glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f)), // 第三个盒子的位置
        // 添加更多位置矩阵
    };

    for (auto& model2 : models) {
        model2 = glm::scale(model2, glm::vec3(scValue, scValue, scValue));
        reflectionBox_->runDrawProcess(model2, view, projection);
    }

        skyB_->runDrawProcess(view,projection); 
        button2D_->runRender();
}

void animationScene::Cleanup() {
    if (!hasInit) {
        // 如果未初始化直接
        return;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderModel_->attachId);

    //glfwTerminate();
    delete shaderModel_;
}

void animationScene::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    animationScene* thiz = (animationScene*)glfwGetWindowUserPointer(window);
    thiz->camera_->ProcessMouseScroll(static_cast<float>(yoffset));
}

void animationScene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // animationScene* thiz = (animationScene*)glfwGetWindowUserPointer(window);
    // if (key == GLFW_KEY_X) {
    //     if (action == GLFW_PRESS) {
    //         thiz->isAnimating = true;
    //     }
    //     else if (action == GLFW_RELEASE) {
    //         thiz->isAnimating = false;
    //         //thiz->m_CurrentTime = 0.0f; // 重置动画时间
    //     }
    // }
}

void animationScene::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    animationScene* thiz = (animationScene*)glfwGetWindowUserPointer(window);
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        //std::cout << "右键点击事件捕获！" << std::endl;
        thiz->enableMouse = !(thiz->enableMouse); 
        if (thiz->enableMouse) {
            glfwSetInputMode(thiz->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(thiz->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

void animationScene::setCallBackControl(void*thiz) {
	animationScene* thiz_ = (animationScene*)thiz;
    if (thiz_ == nullptr) {
        std::cerr<<__FILE__<<" thiz_ is nullptr"<<std::endl;
        return;
    }
    glfwSetFramebufferSizeCallback(thiz_->window, animationScene::framebuffer_size_callback);
    glfwSetCursorPosCallback(thiz_->window, animationScene::mouse_callback);
    glfwSetScrollCallback(thiz_->window, animationScene::scroll_callback);
    glfwSetKeyCallback(thiz_->window,animationScene::keyCallback);
    glfwSetMouseButtonCallback(thiz_->window,animationScene::mouse_button_callback);
    //glfwSetInputMode(thiz_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void animationScene::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    animationScene* thiz = (animationScene*)glfwGetWindowUserPointer(window);
    if (!thiz->enableMouse) {
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
}

void animationScene::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void animationScene::processInput(GLFWwindow *window) {
    
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

    // if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
    //     isAnimating = true;
    // }
    // if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
    //     isAnimating = false;
    //     //m_CurrentTime = 0.0f; // 重置动画时间
    // }
}