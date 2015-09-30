#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "lib/PracticalSocket.h"


class Server
{
private:
    int _adress;
    int _port;
    int _clients;
    UDPSocket* _listener;
public:
    Server(const unsigned int port);
    void waitForClients();
    ~Server();
};

#endif
