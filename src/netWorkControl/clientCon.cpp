#include "clientCon.h"
#include <iostream>
#include <cstring>
#include <unistd.h>


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
        exit(1);
    }
    std::cout << "Connected to server!" << std::endl;
    return true;
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

void clientCon::sendTLVMessage(int type, const std::string& message) {
    int messageLength = message.length();

    // 发送消息类型
    send(clientSocket, (char*)&type, sizeof(type), 0);
    // 发送消息长度
    send(clientSocket, (char*)&messageLength, sizeof(messageLength), 0);
    // 发送消息内容
    send(clientSocket, message.c_str(), messageLength, 0);
}
