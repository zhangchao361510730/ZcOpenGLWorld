#ifndef modelShow_H_
#define modelShow_H_
#include"baseInit.h"

class camera;
class meshTool;
class ShaderGLSLTool;

class modelShow:public baseInit {
private:
    uint32_t EBO;
    camera* camera_;
    meshTool* meshTool_;
    ShaderGLSLTool* ShaderGLSLTool_;

    float lastX = windowsWidth / 2.0f;
    float lastY = windowsHeight / 2.0f;
    bool firstMouse = true;
    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

public:
    modelShow(/* args */);
    ~modelShow();
    static void setCallBackControl(void*);
    bool InitGlSource()override;
    void runDrawProcess()override;
    bool unInitResource();
};

#endif