#ifndef SceneManager_H_
#define SceneManager_H_

#include"scene.hpp"

class SceneManager {
private:
    Scene* currentScene;

public:
    SceneManager() : currentScene(nullptr) {}

    void ChangeScene(Scene* newScene) {
        if (currentScene) {
            currentScene->Cleanup();  // 清理当前场景
            delete currentScene;
        }
        currentScene = newScene;
        currentScene->Init();  // 初始化新场景
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