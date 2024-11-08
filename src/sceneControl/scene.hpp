class Scene {
public:
    virtual ~Scene() = default;

    virtual void Init() = 0;         // 初始化场景
    virtual void Update(float dt) = 0;  // 更新场景逻辑
    virtual void Render() = 0;       // 渲染场景
    virtual void Cleanup() = 0;      // 清理场景资源
};
