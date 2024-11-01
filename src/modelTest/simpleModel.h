#ifndef simpleModel_H_
#define simpleModel_H_
#include"baseInit.h"

class cameraTool;
class loadModelTool;
class ShaderGLSLTool;

class simpleModel:public baseInit {
private:
    uint32_t EBO;
    cameraTool* camera_;
    loadModelTool* loadModelTool_;
    float lastX = windowsWidth / 2.0f;
    float lastY = windowsHeight / 2.0f;
    bool firstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

public:
    simpleModel(/* args */);
    ~simpleModel();
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