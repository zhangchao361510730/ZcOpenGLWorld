#ifndef SERVERCON_H
#define SERVERCON_H

#include <string>
#include <memory>
#include <arpa/inet.h>
#include "globaDefine.h"

class SceneManager;
class mainLoop;

class serverCon {
public:
    serverCon(int port);
    ~serverCon();
    void startServer();
    mainLoop* mainLoop_ = nullptr;
    SceneManager* SceneManager_ = nullptr;
    _processMessage_ messageProcessCallback = nullptr;
private:
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int port;
    void handleClient();
    static void RecvMessageLoop(void* thiz);
    void processMessage(const char* message, int length);
};

#endif // SERVERCON_H
