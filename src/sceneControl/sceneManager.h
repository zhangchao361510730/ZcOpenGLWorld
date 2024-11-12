#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#ifdef PLATFORM_UNIX
#include <unistd.h>
#endif
#include <memory>
#include "serverCon.h"
#include "clientCon.h"

// 前置声明
class serverCon;
class clientCon;
class mainLoop;
class Scene;

class SceneManager {
public:
    Scene* currentScene = nullptr;
    uint16_t runType = 3;  // 1 表示服务器，2 表示客户端，3 表示未知（单机模式）
    std::shared_ptr<serverCon> serverPtr_;
    std::shared_ptr<clientCon> clientPtr_;
    mainLoop* mainLoop_ = nullptr;
    uint16_t currentNumber = -1;
    bool hasConnected = false;
    SceneManager();

    bool sendNetMessage();
    void ChangeScene(Scene* newScene);
    bool newSceneInit();
    void Update(float dt);
    void Render();
    void setServerPtr();
    void setClientPtr();
};

#endif  // SCENEMANAGER_H_
