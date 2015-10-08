#include "PacketSendMap.h"

PacketSendMap::PacketSendMap() :  Packet(NETWORK_SENDMAP)
{

}


void PacketSendMap::prepare(SceneGame* scene)
{
    
}

void PacketSendMap::process(SceneGame* scene, sf::UdpSocket &socket, sf::IpAddress &distant, unsigned short port)
{

}
