#include"skyBox.h"
#include"mainLoop.h"
#include"cameraTool.h"
#include"button2D.h"
#include"reflectionBox.h"
#include"animationTool.h"
#include"loadModelTool.h"
#include"shaderLanguage.h"
#include"modelBindAnimation.h"

mainLoop::mainLoop(/* args */) {

}

mainLoop::~mainLoop() {

}

void mainLoop::glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

bool mainLoop::InitGlSource() {
	//setCallbackFun_ = mainLoop::setCallBackControl;
    glfwSetErrorCallback(mainLoop::glfw_error_callback);
	baseInit::InitGlSource();
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).


    //glm::mat4 projection = glm::ortho(0.0f, (float)windowsWidth, (float)windowsHeight, 0.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //stbi_set_flip_vertically_on_load(true);// load model need 

    sceneManager = new SceneManager();
    return true;
}

void mainLoop::runDrawProcess() {
    // render loop
    while (!glfwWindowShouldClose(window)) {
       
        switch (sceneNumber) {
            case 1:{
                if (sceneManager->currentNumber != 1) {
                    sceneManager->ChangeScene(new animationScene(window));
                    sceneManager->newSceneInit();
                    sceneManager->currentNumber = 1;
                }
                break;
            }
            case 2:{
                if (sceneManager->currentNumber != 2) {
                    sceneManager->ChangeScene(new setScene(window));
                    sceneManager->currentNumber = 2;
                }
                break;
            }
            default:{
                break;
            }
        }
        float currentFrame = glfwGetTime();
        sceneManager->Update(currentFrame);
        glfwPollEvents();
        sceneManager->Render();

        glfwSwapBuffers(window);

    }
    unInitResource();
}

void mainLoop::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// void mainLoop::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
//     mainLoop* thiz = (mainLoop*)glfwGetWindowUserPointer(window);
//     if (!thiz->enableMouse) {
//     float xpos = static_cast<float>(xposIn);
//     float ypos = static_cast<float>(yposIn);
//     if (thiz->firstMouse) {
//         thiz->lastX = xpos;
//         thiz->lastY = ypos;
//         thiz->firstMouse = false;
//     }
//     float xoffset = xpos - thiz->lastX;
//     float yoffset = thiz->lastY - ypos; // reversed since y-coordinates go from bottom to top
//     thiz->lastX = xpos;
//     thiz->lastY = ypos;
//     thiz->camera_->ProcessMouseMovement(xoffset, yoffset);
//     }
// }

// void mainLoop::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//     mainLoop* thiz = (mainLoop*)glfwGetWindowUserPointer(window);
//     thiz->camera_->ProcessMouseScroll(static_cast<float>(yoffset));
// }

// void mainLoop::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     // mainLoop* thiz = (mainLoop*)glfwGetWindowUserPointer(window);
//     // if (key == GLFW_KEY_X) {
//     //     if (action == GLFW_PRESS) {
//     //         thiz->isAnimating = true;
//     //     }
//     //     else if (action == GLFW_RELEASE) {
//     //         thiz->isAnimating = false;
//     //         //thiz->m_CurrentTime = 0.0f; // 重置动画时间
//     //     }
//     // }
// }

// void mainLoop::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
//     mainLoop* thiz = (mainLoop*)glfwGetWindowUserPointer(window);
//     if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
//         //std::cout << "右键点击事件捕获！" << std::endl;
//         thiz->enableMouse = !(thiz->enableMouse); 
//         if (thiz->enableMouse) {
//             glfwSetInputMode(thiz->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//         } else {
//             glfwSetInputMode(thiz->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//         }
//     }
// }

// void mainLoop::setCallBackControl(void*thiz) {
// 	mainLoop* thiz_ = (mainLoop*)thiz;
//     if (thiz_ == nullptr) {
//         std::cerr<<__FILE__<<" thiz_ is nullptr"<<std::endl;
//         return;
//     }
//     glfwSetFramebufferSizeCallback(thiz_->window, mainLoop::framebuffer_size_callback);
//     glfwSetCursorPosCallback(thiz_->window, mainLoop::mouse_callback);
//     glfwSetScrollCallback(thiz_->window, mainLoop::scroll_callback);
//     glfwSetKeyCallback(thiz_->window,mainLoop::keyCallback);
//     glfwSetMouseButtonCallback(thiz_->window,mainLoop::mouse_button_callback);
//     //glfwSetInputMode(thiz_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
// }

void mainLoop::processInput(GLFWwindow *window) {
    
    // if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    //     glfwSetWindowShouldClose(window, true);
    // }

    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera_->ProcessKeyboard(FORWARD, m_DeltaTime);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera_->ProcessKeyboard(BACKWARD, m_DeltaTime);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera_->ProcessKeyboard(LEFT, m_DeltaTime);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera_->ProcessKeyboard(RIGHT, m_DeltaTime);

    // if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
    //     isAnimating = true;
    // }
    // if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
    //     isAnimating = false;
    //     //m_CurrentTime = 0.0f; // 重置动画时间
    // }
}


bool mainLoop::unInitResource() {

    return true;
}