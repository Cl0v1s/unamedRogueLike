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
	char* data = (char *)"ready to rock !";
	_socket->send(data, 32, server, NETWORK_PORT);
	//attente de la r�c�ption du port
	char buffer[1024];
	size_t received;
	_socket->receive(buffer, sizeof(buffer), received, server, _serverPort);
	//traitement des donn�es
	sscanf(buffer, "%d:%d;", &command, &args);
	if(command == NETWORK_SENDPORT)
	{
		_server = server;
		_serverPort = args;
		std::cout << "Connexion établie au serveur a l'adresse " << _server << " sur le port " <<  _serverPort << std::endl;
	}
	else
	{
		assert("Message inattendu.");
		exit(1);
	}
}

bool Client::isAlive()
{
	return alive;
}

void Client::update()
{
	bool done = false;
	char buffer[1024];
	size_t received;
	sf::IpAddress distant;
	unsigned short distant_port;
	int command;
	int args;
	while(!done)
	{
		_socket->receive(buffer, sizeof(buffer), received, distant, distant_port);
		//controle de l'origine du paquet
		if(distant != _server)
		{
			assert("Paquet ne provenant pas du server recu.");
		}
		sscanf(buffer, "%d:%d", &command, &args);
	}
}

Client::~Client()
{
}
