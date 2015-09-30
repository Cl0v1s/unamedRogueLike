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
	else if (strcmp(data, "we salute you !") == 0)
	{
		_alive = false;
		std::cout << "Reception du code d'arret " << sender.toString() << std::endl;
	}
	else
		std::cout << "Message incomprehensible recu de " << sender << std::endl;
}

void Server::manageClient(sf::IpAddress client)
{

}

Server::~Server()
{
	delete _listener;
	for (unsigned int i = 0; i != _clients.size(); i++)
	{
		delete _clients[i];
	}
	std::cout << "Fermeture du serveur" << std::endl;
}
