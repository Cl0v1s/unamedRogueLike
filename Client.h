#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdio>

#include <SFML/Network.hpp>

#include "Const.h"
#include "Packet.h"
#include "SceneGame.h"
#include "PacketAskMap.h"


class Client
{
private:
	sf::UdpSocket* _socket;
	sf::IpAddress _server;
	unsigned short _serverPort;
	bool alive;
	SceneGame* _scene;
public:
	Client(SceneGame *scene, sf::IpAddress server);
	void prepare();
	void update();
	bool isAlive();
	~Client();
};

#endif
