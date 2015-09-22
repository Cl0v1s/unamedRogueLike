#include "SceneGame.h"


SceneGame::SceneGame()
{
	_dungeon = new Dungeon();
	_dungeon->generateRooms();
	_canvas[0] = 0;
	_canvas[1] = 1;
}


SceneGame::~SceneGame()
{
	if (_dungeon != 0x00)
		delete _dungeon;
}

void SceneGame::draw(sf::RenderWindow* render)
{
	//Dessin de la map
	_dungeon->draw(render, _canvas[0], _canvas[1]);
}

void SceneGame::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_canvas[0] -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_canvas[0] += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_canvas[1] -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_canvas[1] += 1;
	}
}
