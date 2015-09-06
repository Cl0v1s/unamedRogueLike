#include "SceneGame.h"


SceneGame::SceneGame()
{
	dungeon = new Dungeon();
	dungeon->generateRooms();
	canvas.x = 0;
	canvas.y = 0;
}


SceneGame::~SceneGame()
{
	if (dungeon != 0x00)
		delete dungeon;
}

void SceneGame::draw(sf::RenderWindow* render)
{

}

void SceneGame::update()
{

}
