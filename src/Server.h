#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>

#include <SFML/Network.hpp>


#include "Const.h"
#include "SceneGame.h"
#include "Packet.h"


class Server
{
private:
	bool _alive;
    int _adress;
    int _port;
	std::vector<std::thread*> _clients;
	std::vector<int> _clientPorts;
    sf::UdpSocket* _listener;
	SceneGame* _scene;
public:
    Server(SceneGame* scene, const unsigned int port);
    void waitForClients();
	bool isAlive();
	void manageClient(sf::IpAddress client);
    ~Server();
};

#endif
