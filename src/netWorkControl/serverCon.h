
#ifndef SERVERCON_H
#define SERVERCON_H

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>


class serverCon {
public:
    serverCon(int port);
    ~serverCon();
    void startServer();

private:
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int port;
};

#endif // SERVERCON_H