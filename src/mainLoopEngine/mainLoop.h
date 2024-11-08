#ifndef skeletalAnimation_H_
#define skeletalAnimation_H_
#include"baseInit.h"
#include"sceneManager.hpp"
#include"setScene.h"
#include"animationScene.h"


class skyBox;
class button2D;
class cameraTool;
class loadModelTool;
class loadAnimation;
class animationTool;
class reflectionBox;

class modelBindAnimation;

class mainLoop:public baseInit {
private:
    SceneManager *sceneManager;

    uint16_t sceneNumber = 1;
    bool enableMouse = true;
    float lastX = windowsWidth / 2.0f;
    float lastY = windowsHeight / 2.0f;
    bool firstMouse = true;
    float m_DeltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool isAnimating = false;
    float m_CurrentTime = 0.0f;
    friend class animationTool;
public:
    mainLoop(/* args */);
    ~mainLoop();
    static void glfw_error_callback(int error, const char* description);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void setCallBackControl(void*thiz);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void processInput(GLFWwindow* window)override;
    bool InitGlSource()override;
    void runDrawProcess()override;
    bool unInitResource();
};

#endif