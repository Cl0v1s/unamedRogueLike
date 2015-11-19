#ifndef PACKET_ASK_MAP_H
#define PACKET_ASK_MAP_H

#include <SFML/Network.hpp>

#include "Packet.h"
#include "PacketSendMap.h"
#include "SceneGame.h"
#include "Const.h"

class PacketAskMap :
	public Packet
{
public:
	PacketAskMap();
	void prepare(SceneGame* scene);
	void process(SceneGame* scene, sf::UdpSocket &socket, sf::IpAddress &distant, unsigned short port);
	~PacketAskMap();
};

#endif

