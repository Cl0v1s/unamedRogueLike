#include "Client.h"


Client::Client(SceneGame *scene, sf::IpAddress server)
{
	alive = true;
	_scene = scene; 
	unsigned short server_port;
	int command;
	int args;
	//creation de la lisaison durable sur le serveur
	_socket = new sf::UdpSocket();
	if (_socket->bind(NETWORK_PORT+1) != sf::Socket::Done)
	{
		assert("Impossible d'ouvrir le port d'ecoute pour le serveur !");
	}
	std::cout << "Tentative de connexion vers " << server.toString() << std::endl;
	char* data = "ready to rock !";
	_socket->send(data, 32, server, NETWORK_PORT);
	//attente de la récéption du port
	char buffer[1024];
	size_t received;
	_socket->receive(buffer, sizeof(buffer), received, server, server_port);
	//traitement des données
	std::cout << "recu " << buffer << std::endl;
	sscanf(buffer, "%d:%d;", &command, &args);
	

}

bool Client::isAlive()
{
	return alive;
}

void Client::update()
{
	bool done = false;
	sf::IpAddress distant;
	unsigned short port;
	size_t received;
	char msg[4];
	Packet* currentPacket = 0x00;
	while (!done)
	{
		std::cout << "En attente de messages..." << std::endl;
		_socket->receive(msg, 4, received, distant, port);
		std::cout << "Reception du msg " << msg[0] << std::endl;
		//traitement du packet de port
		switch (msg[0])
		{
		case NETWORK_STOP: //execution et supression du paquet courant
			if (currentPacket != 0x00)
			{
				currentPacket->process(_scene);
				delete currentPacket;
			}
			break;
		default:
			if (currentPacket != 0x00)
			{
				int d = 0;
				//rassemblement des donnes en un seul entier 
				for (unsigned int i = 0; i != received; i++)
				{
					d = d | msg[i];
					d = d << 8;
				}
				currentPacket->addData(d);
			}
			break;
		}

	}
}

Client::~Client()
{
}
