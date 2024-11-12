#include "serverCon.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include<mainLoop.h>

serverCon::serverCon(int port) : port(port) {
    // 创建 socket
    selfType = "server";
    netWorkSock = socket(AF_INET, SOCK_STREAM, 0);
    if (netWorkSock < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        exit(1);
    }

    int opt = 1;
    if (setsockopt(netWorkSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
        close(netWorkSock);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
}

serverCon::~serverCon() {
    close(netWorkSock);
    close(netWorkSock);
}

void serverCon::startServer() {
    if (bind(netWorkSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind failed!" << std::endl;
        return;
    }

    if (listen(netWorkSock, 3) < 0) {
        std::cerr << "Listen failed!" << std::endl;
        return;
    }

    std::cout << "Waiting for client to connect..." << std::endl;

    socklen_t clientAddrSize = sizeof(clientAddr);
    mainLoop_->sceneNumber = 1;
    SceneManager_->runType = 1;
    netWorkSock = accept(netWorkSock, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (netWorkSock < 0) {
        std::cerr << "Client connection failed!" << std::endl;
        return;
    }
    SceneManager_->hasConnected = true;

    std::cout << "Client connected!" << std::endl;
}


