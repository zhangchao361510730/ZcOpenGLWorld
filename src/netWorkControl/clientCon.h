#ifndef CLIENTCON_H
#define CLIENTCON_H

#include <string>
#include <memory>
#include <arpa/inet.h>
#include"globaDefine.h"
#include"netControl.h"

class clientCon:public netControl {
public:
    clientCon(const std::string& serverAddress, int port);
    ~clientCon();
    bool connectToServer();
    void sendMessage(const std::string& message);
private:

    struct sockaddr_in serverAddr;
    std::string serverAddress;
    int port;

    void sendTLVMessage(int type, const std::string& message);
};

#endif // CLIENTCON_H
