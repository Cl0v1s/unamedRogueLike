#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include <SFML/System.hpp>

#include "Scene.h"
#include "Dungeon.h"


class SceneGame :
	public Scene
{
private:
	Dungeon* _dungeon;
	int _canvas[2];

public:
	SceneGame();
	void draw(sf::RenderWindow* render);
	void update();
	virtual ~SceneGame();
};

#endif 
