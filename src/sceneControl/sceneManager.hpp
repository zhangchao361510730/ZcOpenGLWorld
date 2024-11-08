#ifndef SceneManager_H_
#define SceneManager_H_

#include"scene.hpp"
#ifdef PLATFORM_UNIX
#include <unistd.h>
#endif

class SceneManager {
private:
    Scene* currentScene = nullptr;

public:
    SceneManager() : currentScene(nullptr) {}
    uint16_t currentNumber = -1;
    void ChangeScene(Scene* newScene) {
        if (currentScene) {
            currentScene->Cleanup();  // 清理当前场景
            delete currentScene;
        }
        currentScene = newScene;
        
    }
    bool newSceneInit() {
        currentScene->Init();  // 初始化新场景
        return true;
    }

    void Update(float dt) {
        if (currentScene) {
            currentScene->Update(dt);
        }
    }

    void Render() {
        if (currentScene) {
            currentScene->Render();
        }
    }
};

#endif