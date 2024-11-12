#include"netControl.h"
#include"sceneManager.h"
#include<iostream>
#include<vector>
#include<memory.h>


void netControl::sendTLVMessage(int type, const std::string& message) {
    int messageLength = message.length();
    int totalLength = sizeof(type) + sizeof(messageLength) + messageLength;

    // 创建一个缓冲区以容纳类型、长度和内容
    std::vector<char> buffer(totalLength);

    // 将类型、长度和消息内容复制到缓冲区
    memcpy(buffer.data(), &type, sizeof(type));
    memcpy(buffer.data() + sizeof(type), &messageLength, sizeof(messageLength));
    memcpy(buffer.data() + sizeof(type) + sizeof(messageLength), message.c_str(), messageLength);

    // 一次性发送缓冲区中的所有数据
    send(clientSocket, buffer.data(), totalLength, 0);
}

void netControl::RecvMessageLoop(void* thiz) {
        netControl* thiz_ = (netControl* )thiz;
        std::cout<<thiz_->selfType<<" ruing netControl::RecvMessageLoop"<<std::endl;
        while (true) {
            int type;
            int length;
            int bytesReceived = recv(thiz_->clientSocket, (char*)&type, sizeof(type), 0);
            if (bytesReceived <= 0) {
                std::cerr<<"bytesReceived is "<<bytesReceived<<std::endl;
                break;
            }

            bytesReceived = recv(thiz_->clientSocket, (char*)&length, sizeof(length), 0);
            if (bytesReceived <= 0) {
                std::cerr<<"bytesReceived is "<<bytesReceived<<std::endl;
                break;
            }

            // 使用智能指针管理内存
            //std::unique_ptr<char[]> buffer = std::unique_ptr<char[]>(length);
            std::unique_ptr<char[]> buffer(new char[length]);    
            bytesReceived = recv(thiz_->clientSocket, buffer.get(), length, 0);
            if (bytesReceived <= 0) {
                std::cerr<<"bytesReceived is "<<bytesReceived<<std::endl;
                break;
            }

            // 处理接收到的消息
            if (thiz_->messageProcessCallback != nullptr) {
                thiz_->messageProcessCallback(type,buffer.get(), length,(void*)(thiz_->SceneManager_->currentScene));
            } else {
                std::cout<<"mess "<<buffer.get()<<std::endl;
            }
        }
        std::cerr<<"End netControl::RecvMessageLoop "<<std::endl;
    }