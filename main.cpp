#include <stdlib.h>
#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "Const.h"
#include "Scene.h"
#include "SceneGame.h"

int main()
{
	//initialisation du jeu
	//initialisation de la fenetre
	sf::RenderWindow window(sf::VideoMode(DEVICE_WIDTH, DEVICE_HEIGHT), "AcrossTheDungeon");
	srand(time(0x00));
	Scene* current_scene = new SceneGame();
	while (window.isOpen())
	{
		//gestion de la logique
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (current_scene != 0x00)
			current_scene->update();

		//gestion de l'affichage
		window.clear();
		if (current_scene != 0x00)
			current_scene->draw(&window);
		window.display();
	}

	return 0;
}