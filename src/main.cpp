#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <thread>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Const.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Server.h"
#include "Client.h"

void start_server(SceneGame *scene)
{
	srand(time(0x00));
	Server server(scene, NETWORK_PORT);
	while(server.isAlive())
	{
		//boucle d'attente de clients
		server.waitForClients();
	}
}

void start_client(SceneGame *scene)
{
	srand(time(0x00));
	Client client(scene, sf::IpAddress("127.0.0.1"));
	while (client.isAlive())
	{
		client.update();
	}
}


int main(int argc, char **argv)
{
	Scene* current_scene;
	SceneGame* scene_game;
    //gestion du framerate
    sf::Clock timer;
    std::thread* online;
	if (strcmp(argv[1], "-client") == 0) {
		scene_game = new SceneGame(GameType::client);
    	//gestion du multijoueur
    	online = new std::thread(start_client, scene_game);
	} else if (strcmp(argv[1], "-serveur") == 0) {
		scene_game = new SceneGame(GameType::server);
    	//gestion du multijoueur
    	online = new std::thread(start_server, scene_game);
    } else {
        printf("Utilisation :\n\"%s -serveur\" si vous voulez être le serveur\n\"%s -client\" si vous voulez être le client\n", argv[0], argv[0]);
        return 0;
    }
    current_scene = scene_game;
	//initialisation du jeu
	//initialisation de la fenetre
	sf::RenderWindow window(sf::VideoMode(DEVICE_WIDTH, DEVICE_HEIGHT), "AcrossTheDungeon");
	srand(time(0x00));
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
	std::stringstream ss; ss << NETWORK_KILL << ":0";
	sender.send("we salute you !", 32, recipient, NETWORK_PORT);
	sender.send(ss.str().c_str(), sizeof(ss), recipient, NETWORK_PORT+1);

	//atteindre la fin du thread online
	online->join();
	delete online;
	return 0;
}
