#include "Packet.h"

Packet::Packet()
{

}

Packet::Packet(unsigned char code)
{
	_code = code;
}

void Packet::addData(int data)
{
	_data.push_back(data);
}

void Packet::send(sf::UdpSocket &socket, sf::IpAddress distant, const unsigned short port)
{
	socket.send((char*)_code, 1, distant, port);
	for (unsigned int i = 0; i != _data.size(); i++)
	{
		socket.send((char*)_data[i],4, distant, port);
	}
	socket.send((char*)NETWORK_STOP, 1, distant, port);
}

Packet::~Packet()
{
}
