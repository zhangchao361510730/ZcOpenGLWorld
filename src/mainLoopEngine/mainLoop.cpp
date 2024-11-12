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
    glfwSetErrorCallback(mainLoop::glfw_error_callback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(windowsWidth, windowsHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    if (setCallbackFun_ != nullptr) {
        setCallbackFun_(this);
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    sceneManager = new SceneManager();
    sceneManager->mainLoop_ = this;
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
                    sceneManager->ChangeScene(new setScene(window,&sceneNumber));
                    sceneManager->newSceneInit();
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

bool mainLoop::unInitResource() {

    return true;
}