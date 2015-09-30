#include "Server.h"

Server::Server(const unsigned int port)
{
	_alive = true;
    _port = port;
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
	}
	else
		std::cout << "Message incomprehensible recu de " << sender << std::endl;
}

void Server::manageClient(sf::IpAddress client)
{
	//sélection d'un port aléatoire au dessus du port 1024
	int port = rand() % (65536 - 2048) + 2048;
	_clientPorts.push_back(port);
	//création du pprt d'écoute
	sf::UdpSocket receiver;
	while (receiver.bind(port) != sf::Socket::Done)
	{
		port = rand() % (65536 - 2048) + 2048;
	}
	//création du port d'envoi de données vers le client
	sf::UdpSocket sender;
	//détermination du message
	int data = NETWORK_SENDPORT; data = data << 24; data = data | port;
	//envoi du message contenant le port sur lequel le client peut communiquer
	sender.send((char*)data, 4, client, NETWORK_PORT);
	//boucle de réception des données
	bool done = false;
	size_t received;
	char msg[4];
	unsigned short client_port;
	while (!done)
	{
		if (receiver.receive(msg, 4, received, client, client_port) != sf::Socket::Done)
		{
			assert("Erreur lors de la réception des données.");
		}
		//traitement des données
		//traitement du message  d'arret du thread
		if (msg[0] == NETWORK_KILL && client.toString() == "127.0.0.1")
		{
			done = true;
		}
		//traiter ici les autres commandes
	}
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
