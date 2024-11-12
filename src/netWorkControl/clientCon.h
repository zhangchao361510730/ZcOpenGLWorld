#ifndef CLIENTCON_H
#define CLIENTCON_H

#include <string>
#include <memory>
#include <arpa/inet.h>

class SceneManager;
class mainLoop;


class clientCon {
public:
    clientCon(const std::string& serverAddress, int port);
    ~clientCon();
    bool connectToServer();
    void sendMessage(const std::string& message);
    mainLoop* mainLoop_ = nullptr;
    SceneManager* SceneManager_ = nullptr;
private:
    int clientSocket;
    struct sockaddr_in serverAddr;
    std::string serverAddress;
    int port;

    void sendTLVMessage(int type, const std::string& message);
};

#endif // CLIENTCON_H
