#ifndef SERVERCON_H
#define SERVERCON_H

#include"netControl.h"

class serverCon :public netControl {
public:
    serverCon(int port);
    ~serverCon();
    void startServer();
private:
    struct sockaddr_in serverAddr, clientAddr;
    int port;
};

#endif // SERVERCON_H
