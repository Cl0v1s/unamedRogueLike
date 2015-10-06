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
	Packet* current = 0x00;
	while(!done)
	{
		_socket->receive(buffer, sizeof(buffer), received, distant, distant_port);
		//controle de l'origine du paquet
		if(distant != _server && distant != sf::IpAddress("127.0.0.1"))
		{
			assert("Paquet ne provenant pas d'un auteur autorise.");
		}
		else
		{
			sscanf(buffer, "%d:%d", &command, &args);
			switch(command)
			{
				case NETWORK_KILL:
					done = true;
					break;
				case NETWORK_STOP:
					if(current != 0x00)
					{
						current->process(_scene);
						delete current;
					}
				break;
				case NETWORK_NEXT:
					if(current != 0x00)
						current->addData(args);
				break;
				default:
					assert("Paquet incompréhensible recu.");
					break;
			}
		}
	}
	std::cout << "Fermeture de la connexion avec le serveur." << std::endl;
}

Client::~Client()
{
}
