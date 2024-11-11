#ifndef SceneManager_H_
#define SceneManager_H_

#include"scene.hpp"
#ifdef PLATFORM_UNIX
#include <unistd.h>
#endif
#include <memory>

class serverCon;
class clientCon;

class SceneManager {
private:
    Scene* currentScene = nullptr;

public:
    std::shared_ptr<serverCon> serverConPtr;
    std::shared_ptr<clientCon> clientPtr_;
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
        currentScene->setSceneManager(this);
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