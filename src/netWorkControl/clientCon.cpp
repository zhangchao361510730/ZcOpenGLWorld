#include "clientCon.h"

clientCon::clientCon(const std::string& serverAddress, int port)
    : serverAddress(serverAddress), port(port) {
    // 创建客户端套接字
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

void clientCon::connectToServer() {
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        exit(1);
    }
    std::cout << "Connected to server!" << std::endl;
}

void clientCon::sendMessage(const std::string& message) {
    send(clientSocket, message.c_str(), message.length(), 0);
    char buffer[512];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // 终止字符串
        std::cout << "Server response: " << buffer << std::endl;
    }
}
