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
	std::stringstream buffer;
	//envoi du code du packet
	buffer << _code << ":0";
	socket.send(buffer.str().c_str(), sizeof(buffer), distant, port);
	//envoi des données
	for(unsigned int i = 0; i != _data.size();i++)
	{
		buffer.str("");
		buffer << NETWORK_NEXT << ":" << _data[i];
		socket.send(buffer.str().c_str(), sizeof(buffer), distant, port);
	}
	//encoi du paquet de fin de transmission
	buffer.str("");
	buffer << NETWORK_STOP << ":0";
	socket.send(buffer.str().c_str(), sizeof(buffer), distant, port);
}

Packet::~Packet()
{
}
