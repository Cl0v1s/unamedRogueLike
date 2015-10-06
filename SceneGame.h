#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include <SFML/System.hpp>

#include "Scene.h"
#include "Dungeon.h"

enum GameType{
	server,
	client,
};

class SceneGame :
	public Scene
{
private:
	Dungeon* _dungeon;
	int _canvas[2];

public:
	SceneGame(GameType type);
	void draw(sf::RenderWindow* render);
	void update();
	Dungeon* getDungeon() const;
	virtual ~SceneGame();
};

#endif
