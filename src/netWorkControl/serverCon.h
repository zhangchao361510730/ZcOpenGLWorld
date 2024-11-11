#ifndef SERVERCON_H
#define SERVERCON_H

#include <string>
#include <memory>
#include <arpa/inet.h>
class serverCon {
public:
    serverCon(int port);
    ~serverCon();
    void startServer();

private:
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int port;

    void handleClient();
    void processMessage(const char* message, int length);
};

#endif // SERVERCON_H
