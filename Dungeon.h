#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdlib.h>
#include <vector>

#include "Const.h"

//définition des structures utiles à la génération
struct Room
{
	unsigned int _x;
	unsigned int _y;
	unsigned char _width;
	unsigned char _height;
};

class Dungeon
{
private:
	char** _map;
	unsigned int _width;
	unsigned int _height;
public:
	Dungeon();

	/// <summary>
	/// Génère les salles du donjon
	/// </summary>
	void generateRooms();

	/// <summary>
	/// Génère les couloirs donjon
	/// </summary>
	void generatePassages(std::vector<Room> &rooms);
	~Dungeon();
};

#endif

