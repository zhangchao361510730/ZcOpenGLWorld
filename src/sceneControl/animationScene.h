#ifndef ANIMATION_SCENE_H_
#define ANIMATION_SCENE_H_

#include"scene.hpp"

class animationScene : public Scene
{
private:
    /* data */
public:
    animationScene(/* args */);
    ~animationScene();
    void Init() override;         // 初始化场景
    void Update(float dt) override;  // 更新场景逻辑
    void Render() override;       // 渲染场景
    void Cleanup() override;      // 清理场景资源
};

#endif