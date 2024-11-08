#ifndef ANIMATION_SCENE_H_
#define ANIMATION_SCENE_H_

#include"scene.hpp"
#include"baseInit.h"

class skyBox;
class button2D;
class cameraTool;
class loadModelTool;
class loadAnimation;
class animationTool;
class reflectionBox;

class modelBindAnimation;

class animationScene : public Scene 
{
private:
    uint32_t EBO;
    skyBox * skyB_;
    button2D * button2D_;
    cameraTool* camera_;
    loadModelTool* loadModelTool_;
    modelBindAnimation* modelBindA_;
    loadAnimation* loadAnimation_;
    animationTool* animationTool_;
    reflectionBox* reflectionBox_;
    uint32_t VBO = 0;
    uint32_t VAO = 0;
    ShaderGLSLTool* shaderModel_;
    ShaderGLSLTool* shaderSkyBox_;

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
    animationScene(/* args */);
    ~animationScene();
    void Init() override;         // 初始化场景
    void Update(float dt) override;  // 更新场景逻辑
    void Render() override;       // 渲染场景
    void Cleanup() override;      // 清理场景资源

    static void glfw_error_callback(int error, const char* description);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void setCallBackControl(void*thiz);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void processInput(GLFWwindow* window);
    // bool InitGlSource()override;
    // void runDrawProcess()override;

};

#endif