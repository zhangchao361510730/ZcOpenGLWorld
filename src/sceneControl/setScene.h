#ifndef SETSCENE_H_
#define SETSCENE_H_

#define subWindHeight 100

#include"sceneManager.hpp"

#include"scene.hpp"
#include<memory>
#include<string>

class serverCon;

class setScene : public Scene
{
private:
    friend class mainLoop;
    // 当前选中的输入框（0 表示 IP，1 表示端口）
    int activeInput = 0;  // 0 表示 IP，1 表示端口
    SceneManager *SceneManager_ = nullptr;
    uint16_t* sceneId_ = nullptr;
    std::shared_ptr<serverCon> serverConPtr;
    // 成员变量
    char ip[16];      // 默认 IP 地址
    char portStr[6];       // 默认端口字符串（方便软键盘输入）
    bool isSingleClickMode = false;
    bool isServerCreated = false;
    bool isConnected = false;
public:
    setScene(GLFWwindow* windows_,uint16_t * sceneId);
    ~setScene();
    void Init() override;         // 初始化场景
    void Update(float dt) override;  // 更新场景逻辑
    void Render() override;       // 渲染场景
    void Cleanup() override;      // 清理场景资源
    void renderUI();
    void startServer();
    void connectToServer();
    inline void setSceneManager(SceneManager * _SceneManager_) {
        SceneManager_ = _SceneManager_;
    }
    void ShowVirtualKeyboard(char* inputBuffer, size_t bufferSize);
};

#endif