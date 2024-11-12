#include "serverCon.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include<mainLoop.h>

serverCon::serverCon(int port) : port(port) {
    // 创建 socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
}

serverCon::~serverCon() {
    close(clientSocket);
    close(serverSocket);
}

void serverCon::startServer() {
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind failed!" << std::endl;
        return;
    }

    if (listen(serverSocket, 3) < 0) {
        std::cerr << "Listen failed!" << std::endl;
        return;
    }

    std::cout << "Waiting for client to connect..." << std::endl;

    socklen_t clientAddrSize = sizeof(clientAddr);
    mainLoop_->sceneNumber = 1;
    SceneManager_->runType = 1;
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Client connection failed!" << std::endl;
        return;
    }

    std::cout << "Client connected!" << std::endl;
    handleClient();
}

void serverCon::handleClient() {
    while (true) {
        // 读取 Type 和 Length
        int type;
        int length;
        int bytesReceived = recv(clientSocket, (char*)&type, sizeof(type), 0);
        if (bytesReceived <= 0) break;

        bytesReceived = recv(clientSocket, (char*)&length, sizeof(length), 0);
        if (bytesReceived <= 0) break;

        // 使用智能指针管理内存
        //std::unique_ptr<char[]> buffer = std::unique_ptr<char[]>(length);
        std::unique_ptr<char[]> buffer(new char[length]);    
        bytesReceived = recv(clientSocket, buffer.get(), length, 0);
        if (bytesReceived <= 0) break;

        // 处理接收到的消息
        processMessage(buffer.get(), length);
    }
}

void serverCon::processMessage(const char* message, int length) {
    std::cout << "Received message: " << std::string(message, length) << std::endl;

    // 发送响应
    const char* response = "Message received!";
    int responseLength = strlen(response);
    send(clientSocket, (char*)&responseLength, sizeof(responseLength), 0);  // 发送响应长度
    send(clientSocket, response, responseLength, 0);  // 发送响应内容
}
