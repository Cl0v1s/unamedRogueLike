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
	srand(time(CELL_EMPTY));
	Scene* current_scene = new SceneGame();
	//gestion du framerate
	sf::Clock timer;
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

	return 0;
}
