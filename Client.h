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


class Client
{
private:
	sf::UdpSocket* _socket;
	bool alive;
	SceneGame* _scene;
public:
	Client(SceneGame *scene, sf::IpAddress server);
	void update();
	bool isAlive();
	~Client();
};

#endif
