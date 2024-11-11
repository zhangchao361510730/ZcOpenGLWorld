

#ifndef CLIENTCON_H
#define CLIENTCON_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

class clientCon {
public:
    clientCon(const std::string& serverAddress, int port);
    ~clientCon();
    void connectToServer();
    void sendMessage(const std::string& message);

private:
    int clientSocket;
    struct sockaddr_in serverAddr;
    std::string serverAddress;
    int port;
};

#endif // CLIENTCON_H
