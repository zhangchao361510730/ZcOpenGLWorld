#include "clientCon.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include<mainLoop.h>

clientCon::clientCon(const std::string& serverAddress, int port) : serverAddress(serverAddress), port(port) {
    std::cout<<"IP is "<<serverAddress<<" port is "<<port<<std::endl;
    selfType = "client";
    netWorkSock = socket(AF_INET, SOCK_STREAM, 0);
    if (netWorkSock < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(serverAddress.c_str());
}

clientCon::~clientCon() {
    close(netWorkSock);
}

bool clientCon::connectToServer() {
    if (connect(netWorkSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        return false;
    } else {
        std::cout << "Connected to server!" << std::endl;
        SceneManager_->runType = 2;
        SceneManager_->hasConnected = true;
        mainLoop_->changeScene(1);
        return true;
    }

}

void clientCon::sendMessage(const std::string& message) {
    sendTLVMessage(1, message);  // 类型 1 代表文本消息

    // 接收服务器响应
    int responseLength;
    recv(netWorkSock, (char*)&responseLength, sizeof(responseLength), 0);  // 接收响应长度
    char buffer[512];
    int bytesReceived = recv(netWorkSock, buffer, responseLength, 0);  // 接收响应内容
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';  // 终止字符串
        std::cout << "Server response: " << buffer << std::endl;
    }
}

