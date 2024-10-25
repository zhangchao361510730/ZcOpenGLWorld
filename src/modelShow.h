#ifndef modelShow_H_
#define modelShow_H_
#include"baseInit.h"

class cameraTool;
class loadModelTool;
class ShaderGLSLTool;

class modelShow:public baseInit {
private:
    uint32_t EBO;
    cameraTool* camera_;
    loadModelTool* meshTool_;
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