#ifndef SceneManager_H_
#define SceneManager_H_

#ifdef PLATFORM_UNIX
#include <unistd.h>
#endif
#include <memory>
#include"scene.hpp"
#include"serverCon.h"
#include"clientCon.h"


class serverCon;
class clientCon;
class mainLoop;

class SceneManager {
private:
    Scene* currentScene = nullptr;

public:
    std::shared_ptr<serverCon> serverPtr_;
    std::shared_ptr<clientCon> clientPtr_;
    mainLoop* mainLoop_ = nullptr;
    SceneManager() : currentScene(nullptr) {}
    uint16_t currentNumber = -1;
    bool sendNetMessage() {
        return true;
    }
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

    void setServerPtr() {
        serverPtr_->SceneManager_ = this;
        serverPtr_->mainLoop_ = mainLoop_;
    }

    void setClientPtr() {
        clientPtr_->SceneManager_ = this;
        clientPtr_->mainLoop_ = mainLoop_;
    }
};



#endif