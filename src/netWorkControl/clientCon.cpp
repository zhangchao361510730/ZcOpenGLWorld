#include "clientCon.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include<mainLoop.h>

clientCon::clientCon(const std::string& serverAddress, int port) : serverAddress(serverAddress), port(port) {
    std::cout<<"IP is "<<serverAddress<<" port is "<<port<<std::endl;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(serverAddress.c_str());
}

clientCon::~clientCon() {
    close(clientSocket);
}

bool clientCon::connectToServer() {
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        return false;
    } else {
        std::cout << "Connected to server!" << std::endl;
        SceneManager_->runType = 2;
        mainLoop_->changeScene(1);
        return true;
    }

}

void clientCon::sendMessage(const std::string& message) {
    sendTLVMessage(1, message);  // 类型 1 代表文本消息

    // 接收服务器响应
    int responseLength;
    recv(clientSocket, (char*)&responseLength, sizeof(responseLength), 0);  // 接收响应长度
    char buffer[512];
    int bytesReceived = recv(clientSocket, buffer, responseLength, 0);  // 接收响应内容
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';  // 终止字符串
        std::cout << "Server response: " << buffer << std::endl;
    }
}

void clientCon::RecvMessageLoop(void* thiz) {
    clientCon* thiz_ = (clientCon* )thiz;
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
            thiz_->messageProcessCallback(buffer.get(), length);
        }
    }
}

void clientCon::sendTLVMessage(int type, const std::string& message) {
    int messageLength = message.length();

    // 发送消息类型
    send(clientSocket, (char*)&type, sizeof(type), 0);
    // 发送消息长度
    send(clientSocket, (char*)&messageLength, sizeof(messageLength), 0);
    // 发送消息内容
    send(clientSocket, message.c_str(), messageLength, 0);
}
