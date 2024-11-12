#include "sceneManager.h"
#include "scene.h"

SceneManager::SceneManager() : currentScene(nullptr) {}

bool SceneManager::sendNetMessage() {
    return true;
}

void SceneManager::ChangeScene(Scene* newScene) {
    if (currentScene) {
        currentScene->Cleanup();  // 清理当前场景
        delete currentScene;
    }
    currentScene = newScene;
}

bool SceneManager::newSceneInit() {
    if (currentScene) {
        currentScene->setSceneManager(this);
        currentScene->Init();  // 初始化新场景
        return true;
    }
    return false;
}

void SceneManager::Update(float dt) {
    if (currentScene) {
        currentScene->Update(dt);
    }
}

void SceneManager::Render() {
    if (currentScene) {
        currentScene->Render();
    }
}

void SceneManager::setServerPtr() {
    if (serverPtr_) {
        serverPtr_->SceneManager_ = this;
        serverPtr_->mainLoop_ = mainLoop_;
    }
}

void SceneManager::setClientPtr() {
    if (clientPtr_) {
        clientPtr_->SceneManager_ = this;
        clientPtr_->mainLoop_ = mainLoop_;
    }
}
