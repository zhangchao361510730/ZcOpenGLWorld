#ifndef CLIENTCON_H
#define CLIENTCON_H

#include <string>
#include <memory>
#include <arpa/inet.h>

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

    void sendTLVMessage(int type, const std::string& message);
};

#endif // CLIENTCON_H
