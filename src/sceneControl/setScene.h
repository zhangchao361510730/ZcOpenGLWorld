#ifndef SETSCENE_H_
#define SETSCENE_H_

#include"scene.hpp"
class setScene : public Scene
{
private:
    /* data */
public:
    setScene(GLFWwindow* windows_);
    ~setScene();
    void Init() override;         // 初始化场景
    void Update(float dt) override;  // 更新场景逻辑
    void Render() override;       // 渲染场景
    void Cleanup() override;      // 清理场景资源
};

#endif