#ifndef SERVERCON_H
#define SERVERCON_H

#include <string>
#include <memory>
#include <arpa/inet.h>

class SceneManager;
class mainLoop;

class serverCon {
public:
    serverCon(int port);
    ~serverCon();
    void startServer();
    mainLoop* mainLoop_ = nullptr;
    SceneManager* SceneManager_ = nullptr;
private:

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int port;

    void handleClient();
    void processMessage(const char* message, int length);
};

#endif // SERVERCON_H
