#include "Server.h"

Server::Server(SceneGame *scene, const unsigned int port)
{
	_alive = true;
    _port = port;
	_scene = scene;
    _listener = new sf::UdpSocket();
	if (_listener->bind(port) != sf::Socket::Done)
	{
		assert("Impossible de créer le port d'écoute.");
	}
	std::cout << "Serveur ouvert sur le port " << port << std::endl;
}

bool Server::isAlive()
{
	return _alive;
}

void Server::waitForClients()
{
	sf::IpAddress sender;
	unsigned short port;
	char data[33];
	std::size_t received;
	if (_listener->receive(data, 100, received, sender, port) != sf::Socket::Done)
	{
		assert("Error lors de l'acceuil du nouveau client.");
	}
	data[received] = '\0'; //Ajout du caractère de fin cstring
	if (strcmp(data, "ready to rock !") == 0)
	{
		_clients.push_back(new std::thread(&Server::manageClient, this, sender));
	}
	else if (strcmp(data, "we salute you !") == 0 && sender.toString() == "127.0.0.1") //le message d'arret du serveur ne peut venir que du poste courant
	{
		_alive = false;
		std::cout << "Reception du code d'arret " << sender.toString() << std::endl;
		//On envoie kill à tout les thread fils
		sf::IpAddress recipient = "localhost";
		std::stringstream ss; ss << NETWORK_KILL << ":0";
		for(unsigned int i = 0; i != _clientPorts.size(); i++)
		{
			_listener->send(ss.str().c_str(), sizeof(ss), recipient, _clientPorts[i]);
		}
	}
	else
		std::cout << "Message incomprehensible recu de " << sender << std::endl;
}

void Server::manageClient(sf::IpAddress client)
{
	srand(time(0x00));
	bool done = false;
	//sélection d'un port aléatoire au dessus du port 1024
	int port = rand() % (65536 - 2048) + 2048;
	//création du pprt d'écoute
	sf::UdpSocket socket;
	while (socket.bind(port) != sf::Socket::Done)
	{
		port = rand() % (65536 - 2048) + 2048;
	}
	_clientPorts.push_back(port);
	std::cout << "Ouverture d'un port d'ecoute pour " << client.toString() << " sur le port " << port << std::endl;
	//détermination du message
	std::stringstream buffer; buffer << NETWORK_SENDPORT << ":" << port;
	//envoi du message
	socket.send(buffer.str().c_str(), sizeof(buffer), client, NETWORK_PORT + 1);
	char data[1024];
	sf::IpAddress distant;
	unsigned short distant_port;
	size_t received;
	int command, args;
	Packet* current = 0x00;
	while(!done)
	{
		//reception des données brutes
		socket.receive(buffer, sizeof(buffer), received, distant, distant_port);
		if(distant != client && distant != sf::IpAddress("127.0.0.1"))
		{
			assert("Paquet recu d'une source illegale.");
		}
		else
		{
			//formatage des données
			sscanf(data, "%d:%d", &command, &args);
			switch (command) {
				case NETWORK_KILL:
					if(distant == sf::IpAddress("127.0.0.1"))
						done = true;
				break;
				case NETWORK_STOP:
					if(current != 0x00)
					{
						current->process(_scene);
						delete current;
					}
					break;
				default:
					if(current != 0x00)
						current->addData(args);
				break;

			}
		}
	}
	//On indique au client que la connexion est terminée
	buffer.str("");buffer << NETWORK_KILL  << ":0";
	socket.send(buffer.str().c_str(), sizeof(buffer), client, NETWORK_PORT +1);
}

Server::~Server()
{
	sf::UdpSocket sender;
	sf::IpAddress here = "127.0.0.1";
	char stop[4]; stop[0] = NETWORK_KILL;
	delete _listener;
	for (unsigned int i = 0; i != _clients.size(); i++)
	{
		//envoi des messages d'arret à tout les threads d'écoute
		sender.send(stop, 4, here, _clientPorts[i]);
		delete _clients[i];
	}
	std::cout << "Fermeture du serveur" << std::endl;
}
