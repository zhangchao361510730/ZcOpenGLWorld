#include"netControl.h"
#include"sceneManager.h"

void netControl::RecvMessageLoop(void* thiz) {
        netControl* thiz_ = (netControl* )thiz;
        while (true) {
            int type;
            int length;
            int bytesReceived = recv(thiz_->clientSocket, (char*)&type, sizeof(type), 0);
            if (bytesReceived <= 0) break;

            bytesReceived = recv(thiz_->clientSocket, (char*)&length, sizeof(length), 0);
            if (bytesReceived <= 0) break;

            // 使用智能指针管理内存
            //std::unique_ptr<char[]> buffer = std::unique_ptr<char[]>(length);
            std::unique_ptr<char[]> buffer(new char[length]);    
            bytesReceived = recv(thiz_->clientSocket, buffer.get(), length, 0);
            if (bytesReceived <= 0) break;

            // 处理接收到的消息
            if (thiz_->messageProcessCallback != nullptr) {
                thiz_->messageProcessCallback(type,buffer.get(), length,(void*)(thiz_->SceneManager_->currentScene));
            }
        }   
    }