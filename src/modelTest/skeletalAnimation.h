#ifndef skeletalAnimation_H_
#define skeletalAnimation_H_
#include"baseInit.h"

class cameraTool;
class loadModelTool;
class modelBindAnimation;
class loadAnimation;
class animationTool;

class skeletalAnimation:public baseInit {
private:
    uint32_t EBO;
    cameraTool* camera_;
    loadModelTool* loadModelTool_;
    modelBindAnimation* modelBindA_;
    loadAnimation* loadAnimation_;
    animationTool* animationTool_;
    float lastX = windowsWidth / 2.0f;
    float lastY = windowsHeight / 2.0f;
    bool firstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

public:
    skeletalAnimation(/* args */);
    ~skeletalAnimation();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void setCallBackControl(void*thiz);
    void processInput(GLFWwindow* window)override;
    bool InitGlSource()override;
    void runDrawProcess()override;
    bool unInitResource();
};

#endif