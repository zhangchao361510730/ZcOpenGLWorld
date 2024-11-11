#include "serverCon.h"

serverCon::serverCon(int port) : port(port) {
    // 创建服务器端套接字
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
    // 绑定套接字到地址
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind failed!" << std::endl;
        return;
    }

    // 监听客户端连接
    if (listen(serverSocket, 3) < 0) {
        std::cerr << "Listen failed!" << std::endl;
        return;
    }

    std::cout << "Waiting for client to connect..." << std::endl;

    socklen_t clientAddrSize = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Client connection failed!" << std::endl;
        return;
    }

    std::cout << "Client connected!" << std::endl;
    char buffer[512];
    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesReceived] = '\0'; // 终止字符串
        std::cout << "Received message: " << buffer << std::endl;
        send(clientSocket, "Message received", 17, 0);  // 发送响应
    }

    if (bytesReceived == 0) {
        std::cout << "Client disconnected" << std::endl;
    } else if (bytesReceived < 0) {
        std::cerr << "Recv failed!" << std::endl;
    }
}
