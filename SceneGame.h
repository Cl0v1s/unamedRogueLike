#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include <SFML/System.hpp>

#include "Scene.h"
#include "Dungeon.h"


class SceneGame :
	public Scene
{
private:
	Dungeon* dungeon;
	sf::Vector2<int> canvas;

public:
	SceneGame();
	void draw(sf::RenderWindow* render);
	void update();
	virtual ~SceneGame();
};

#endif 
