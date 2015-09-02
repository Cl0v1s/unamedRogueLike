#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdlib.h>
#include <vector>

#include "Const.h"

//d�finition des structures utiles � la g�n�ration
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
	/// G�n�re les salles du donjon
	/// </summary>
	void generateRooms();

	/// <summary>
	/// G�n�re les couloirs donjon
	/// </summary>
	void generatePassages(std::vector<Room> &rooms);
	~Dungeon();
};

#endif

