#ifndef SCENE_H_
#define SCENE_H_
#ifdef PLATFORM_UNIX
#include <unistd.h>
#include<cstdint>
#endif
#include"sceneManager.h"
struct GLFWwindow;
class mainLoop;
class SceneManager;


class Scene {    
public:
    Scene(GLFWwindow*window_) {
        window = window_;
    }

    virtual ~Scene() = default;
    bool hasInit = false;
    virtual void setSceneManager(SceneManager * _SceneManager_) = 0;
    GLFWwindow* window = nullptr;
    virtual void Init() = 0;         // 初始化场景
    virtual void Update(float dt) = 0;  // 更新场景逻辑
    virtual void Render() = 0;       // 渲染场景
    virtual void Cleanup() = 0;      // 清理场景资源
};

#endif