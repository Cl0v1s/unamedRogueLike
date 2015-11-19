#include "PacketAskMap.h"


PacketAskMap::PacketAskMap() : Packet(NETWORK_ASKMAP)
{
}

void PacketAskMap::prepare(SceneGame *scene)
{

}

void PacketAskMap::process(SceneGame *scene, sf::UdpSocket &socket, sf::IpAddress &distant, unsigned short port)
{
	//répond en envoyant un paquet send map
	PacketSendMap response;
	response.prepare(scene);
	response.send(socket, distant, port);
}

PacketAskMap::~PacketAskMap()
{
}
