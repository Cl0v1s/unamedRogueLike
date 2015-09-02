#include "Dungeon.h"


Dungeon::Dungeon()
{
	_width = rand() % (DUNGEON_WIDTH_MAX - 50) + 50;
	_height = rand() % (DUNGEON_HEIGHT_MAX - 50) + 50;
	//initialisation de la map
	_map = new char*[_width];
	for (unsigned char i = 0; i != _width; i++)
	{
		_map[i] = new char[_height];
		for (unsigned char u = 0; u != _height; u++)
		{
			_map[i][u] = 0x00; //normalisation de toutes les cases
		}
	}
}

void Dungeon::generateRooms()
{
	std::vector<Room> rooms;
	unsigned char roomsNumber = rand() % DUNGEON_ROOM_MAX + 5;
	//g�n�ration "virtuelle" des salles
	for (unsigned char i = 0; i != roomsNumber; i++)
	{
		rooms.push_back(Room());
		rooms[i]._width = rand() % ROOM_WIDTH_MAX + 5;
		rooms[i]._height = rand() % ROOM_HEIGHT_MAX + 5;
		rooms[i]._x = rand() % DUNGEON_WIDTH_MAX;
		rooms[i]._y = rand() % DUNGEON_HEIGHT_MAX;
		//test de collision avec l'une des salles pr�cedentes
		bool  error = false;
		auto it = rooms.begin();
		while (!error && it != rooms.end())
		{
			if (rooms[i]._x + rooms[i]._width >= it->_x && rooms[i]._x <= it->_x + it->_width) //test de collision horizontal
			{
				if (rooms[i]._y + rooms[i]._height >= it->_y && rooms[i]._y <= it->_y + it->_height) //test de collision vertical
				{
					rooms.pop_back(); //supression de la derni�re salle qui vient d'etre ajout�e si collision
					error = true;
				}
			}
			it++;
		}
		//si le test a r�ussi, application de la salle � la map
		if (error == false)
		{
			for (unsigned int u = rooms[i]._x; u != rooms[i]._x + rooms[i]._width; u++)
			{
				for (unsigned int o = rooms[i]._y; o != rooms[i]._y + rooms[i]._height; o++)
				{
					_map[u][o] = 0x01;
					//application des murs (on ne fait pas de test qui seraient plus couteux qu'utiles)
					_map[rooms[i]._x][o] = 0x02;
					_map[rooms[i]._x + rooms[i]._width - 1][o] = 0x02;
					_map[u][rooms[i]._y] = 0x02;
					_map[u][rooms[i]._y + rooms[i]._height - 1] = 0x02;
				}
			}
		}
	}
	//passage � la g�n�ration des couloirs
	generatePassages(rooms);
}


void Dungeon::generatePassages(std::vector<Room> &rooms)
{

}


Dungeon::~Dungeon()
{
}
