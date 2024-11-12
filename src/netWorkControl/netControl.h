#ifndef netControl_H_
#define netControl_H_
#include <string>
#include <memory>
#include <arpa/inet.h>
#include"globaDefine.h"

class mainLoop;
class SceneManager;

class netControl
{
private:
    /* data */
public:
    std::string selfType;
    netControl(/* args */) = default;
    ~netControl() = default;
    int netWorkSock = -1;
    mainLoop* mainLoop_ = nullptr;
    SceneManager* SceneManager_ = nullptr;
    _processMessage_ messageProcessCallback = nullptr;
    virtual void sendTLVMessage(int type, const std::string& message);
    static void RecvMessageLoop(void* thiz);
};





#endif