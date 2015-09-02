#include <SFML/Graphics.hpp>
#include <iostream>

#include "Scene.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "AcrossTheDungeon");

	Scene* current_scene;
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