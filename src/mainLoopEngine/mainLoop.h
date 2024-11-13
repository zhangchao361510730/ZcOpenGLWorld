#ifndef skeletalAnimation_H_
#define skeletalAnimation_H_

#include"sceneManager.h"
#include"setScene.h"
#include"animationScene.h"
#include"globaDefine.h"

#include<cstdint>
#ifdef PLATFORM_UNIX
#include<unistd.h>
#endif


class skyBox;
class button2D;
class cameraTool;
class loadModelTool;
class loadAnimation;
class animationTool;
class reflectionBox;
class modelBindAnimation;


typedef void(*_setCallBackFun_)(void*);

enum netWorkType {
    unKnow,service,client
};

class mainLoop {
private:
    SceneManager *sceneManager;
    netWorkType netType = netWorkType::unKnow;
  
    bool enableMouse = true;
    float lastX = windowsWidth / 2.0f;
    float lastY = windowsHeight / 2.0f;
    bool firstMouse = true;
    float m_DeltaTime = 0.0f;
    float lastFrame = 0.0f;

    friend class animationTool;
    _setCallBackFun_ setCallbackFun_ = nullptr;
    GLFWwindow* window = nullptr;
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
    bool InitGlSource();
    void runDrawProcess();
    bool unInitResource();
    inline void changeScene(int sceneId) {
        sceneNumber = sceneId;
    }
    uint16_t sceneNumber = 2;
};

#endif