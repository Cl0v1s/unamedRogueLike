#ifndef PACKET_H
#define PACKET_H

#include <vector>

#include <SFML/Network.hpp>

#include "Const.h"
#include "SceneGame.h"

class Packet
{
protected:
	unsigned char _code;
	std::vector<int> _data;
public:
	Packet();
	Packet(unsigned char code);
	void addData(int data);
	void send(sf::UdpSocket &socket, sf::IpAddress distant, const unsigned short port);
	virtual void process(SceneGame *scene) = 0;
	~Packet();
};

#endif

