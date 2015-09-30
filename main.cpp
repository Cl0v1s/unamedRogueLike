#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>

#include "Const.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Server.h"

void start_server(sf::RenderWindow* window)
{
	Server server(NETWORK_PORT);
	while(server.isAlive())
	{
		//boucle d'attente de clients
		server.waitForClients();
	}
}


int main()
{
	//initialisation du jeu
	//initialisation de la fenetre
	sf::RenderWindow window(sf::VideoMode(DEVICE_WIDTH, DEVICE_HEIGHT), "AcrossTheDungeon");
	srand(time(CELL_EMPTY));
	Scene* current_scene = new SceneGame();
	//gestion du framerate
	sf::Clock timer;
	//gestion du thread multijoueur
	std::thread online(start_server, &window);
	while (window.isOpen())
	{
		//gestion de la logique
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//gestion du framerate
		if (timer.getElapsedTime().asMilliseconds() >= 33)
		{
			timer.restart();
			if (current_scene != CELL_EMPTY)
				current_scene->update();

			//gestion de l'affichage
			window.clear();
			if (current_scene != CELL_EMPTY)
				current_scene->draw(&window);
			window.display();
		}
	}
	//on envoie le message d'arret au serveur
	sf::UdpSocket sender;
	sf::IpAddress recipient = "localhost";
	sender.send("we salute you !", 32, recipient, NETWORK_PORT);
	//atteindre la fin du thread online
	online.join();
	return 0;
}
