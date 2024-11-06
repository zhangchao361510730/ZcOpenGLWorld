#ifndef skeletalAnimation_H_
#define skeletalAnimation_H_
#include"baseInit.h"

class skyBox;
class cameraTool;
class loadModelTool;
class loadAnimation;
class animationTool;
class modelBindAnimation;

class mainLoop:public baseInit {
private:
    uint32_t EBO;
    skyBox * skyB_;
    cameraTool* camera_;
    loadModelTool* loadModelTool_;
    modelBindAnimation* modelBindA_;
    loadAnimation* loadAnimation_;
    animationTool* animationTool_;
    std::vector<float>skyboxVertices;
    float lastX = windowsWidth / 2.0f;
    float lastY = windowsHeight / 2.0f;
    bool firstMouse = true;
    float m_DeltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool isAnimating = false;
    float m_CurrentTime = 0.0f;
    friend class animationTool;
    void loadSkyVertices();
    uint32_t skyboxVAO, skyboxVBO;
    uint32_t cubemapTexture;

public:
    mainLoop(/* args */);
    ~mainLoop();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void setCallBackControl(void*thiz);
    uint32_t loadCubemap(std::vector<std::string> &faces);
    void processInput(GLFWwindow* window)override;
    bool InitGlSource()override;
    void runDrawProcess()override;
    bool unInitResource();
};

#endif