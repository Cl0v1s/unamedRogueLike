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
	//génération "virtuelle" des salles
	for (unsigned char i = 0; i != roomsNumber; i++)
	{
		rooms.push_back(Room());
		rooms[i]._width = rand() % (ROOM_WIDTH_MAX - 5) + 5;
		rooms[i]._height = rand() % (ROOM_HEIGHT_MAX- 5) + 5;
		rooms[i]._x = rand() % (_width - rooms[i]._width);
		rooms[i]._y = rand() % (_height - rooms[i]._height);
		rooms[i]._connected = false;
		//test de collision avec l'une des salles précedentes
		bool  error = false;
		auto it = rooms.begin();
		while (!error && it != rooms.end() && (it - rooms.begin()) != i)
		{
			if (rooms[i]._x + rooms[i]._width >= it->_x && rooms[i]._x <= it->_x + it->_width) //test de collision horizontal
			{
				if (rooms[i]._y + rooms[i]._height >= it->_y && rooms[i]._y <= it->_y + it->_height) //test de collision vertical
				{
					//it = rooms.erase(rooms.begin()+i); //supression de la dernière salle qui vient d'etre ajoutée si collision
					error = true;
				}
			}
			it++;
		}
		//si le test a réussi, application de la salle à la map
		if (error == false)
		{
			unsigned int x, y;
			for (unsigned int u = 0; u != rooms[i]._width - 1; u++)
			{
				for (unsigned int o = 0; o != rooms[i]._height - 1; o++)
				{
					std::cout << rooms[i]._height << std::endl;
					x = u + rooms[i]._x;
					y = o + rooms[i]._y;
					//placement du sol
					_map[x][y] = 0x01;
					//placement des murs
					_map[rooms[i]._x][y] = 0x02;
					_map[rooms[i]._x + rooms[i]._width - 1][y] = 0x02;
					_map[x][rooms[i]._y] = 0x02;
					_map[x][rooms[i]._y + rooms[i]._height - 1] = 0x02;


				}
			}

			/*
			for (unsigned int u = rooms[i]._x; u != rooms[i]._x + rooms[i]._width - 1; u++)
			{
				for (unsigned int o = rooms[i]._y; o != rooms[i]._y + rooms[i]._height - 1; o++)
				{
					_map[u][o] = 0x01;
					//application des murs (on ne fait pas de test qui seraient plus couteux qu'utiles)
					_map[rooms[i]._x][o] = 0x02;
					_map[rooms[i]._x + rooms[i]._width - 1][o] = 0x02;
					_map[u][rooms[i]._y] = 0x02;
					_map[u][rooms[i]._y + rooms[i]._height - 1] = 0x02;
				}
			}**/
		}
	}
	//passage à la génération des couloirs
	generatePassages(rooms);
}


void Dungeon::generatePassages(std::vector<Room> &rooms)
{
	//on choisit une salle au hasard
	unsigned int index = rand() % rooms.size();
	//on génère un chemin à partir de cette salle 
	makePath(rooms, rooms[index]);
	//on vérifie que toutes les salles sont connectés
	//passage a false de tout  les bools de cnx des salles
	for (unsigned int i = 0; i != rooms.size(); i++)
		rooms[i]._connected = false;
	//parcours en profondeur du donjon
	dps(rooms, rooms[index]);
	//test de connexion
	bool done = true;
	unsigned int i = 0;
	while (i != rooms.size() && done == true)
	{
		if (rooms[i]._connected == false)
			done = false;
		i++;
	}
	if (done == false)
	{
		std::cout << "Dungeon non connexe, retry" << std::endl;
		generatePassages(rooms);
	}
	else
		std::cout << "Generation du donjon terminee" << std::endl;
}

void Dungeon::makePath(std::vector<Room> &rooms, Room &origin)
{
	std::vector<Room*> path;
	//on détermine la longueur du chemin
	unsigned int pathLenght = rand() % (rooms.size() - 2) + 2;
	//on ajoute le sommet d'origine au chemin
	path.push_back(&origin);
	//on choisit des salles au hasard
	unsigned int index;
	for (unsigned int i = 0; i != pathLenght; i++)
	{
		index = rand() % (rooms.size());
		path.push_back(&rooms[index]);
	}
	//une fois que le chemin est déterminé, on trace le chemin dans la map
	index = 0;
	Point start, end, current;
	while ((index+1) < path.size())
	{
		//on indique aux salles qu'elles sont voisines
		path[index]->_neibhours.push_back(index + 1);
		path[index + 1]->_neibhours.push_back(index);
		//on recherche des points d'ancrage pour le chemin
		searchAnchorPoint((*path[index]), start);
		searchAnchorPoint((*path[index+1]), end);
		//on place le point courant sur le point d'ancrage de départ
		current = start;
		_map[current._x][current._y] = 0x01;
		//tant qu'on a pas atteint la fin 
		while (current._x != end._x && current._y != end._y)
		{
			if (current._x < end._x)
			{
				current._x += 1;
				_map[current._x][current._y + 1] = 0x02;
				_map[current._x][current._y - 1] = 0x02;
			}
			else if (current._x > end._x)
			{
				current._x -= 1;
				_map[current._x][current._y + 1] = 0x02;
				_map[current._x][current._y - 1] = 0x02;
			}
			else if (current._y < end._y)
			{
				current._y += 1;
				_map[current._x+1][current._y] = 0x02;
				_map[current._x-1][current._y] = 0x02;
			}
			else if (current._y > end._y)
			{
				current._y -= 1;
				_map[current._x + 1][current._y] = 0x02;
				_map[current._x - 1][current._y] = 0x02;
			}
			
			_map[current._x][current._y] = 0x01;
		}
		index += 1;
	}
}


void Dungeon::searchAnchorPoint(Room &room, Point &anchor)
{
	unsigned int side = rand() % 4;
	switch (side)
	{
	case 0:
		anchor._x = room._x;
		anchor._y = rand() % (room._y + (room._height - 2) - 2) + 2;
		break;
	case 1:
		anchor._y = room._y;
		anchor._x = rand() % (room._x + (room._width - 2) - 2) + 2;
		break;
	case 2:
		anchor._x = room._x + room._width -1 ;
		anchor._y = rand() % (room._y + (room._height - 2) - 2) + 2;
		break;
	case 3:
		anchor._y = room._y + room._height - 1;
		anchor._x = rand() % (room._x + (room._width - 2) - 2) + 2;
		break;
	}
}

void Dungeon::dps(std::vector<Room> &rooms, Room &origin)
{
	origin._connected = true;
	for (unsigned int i = 0; i != origin._neibhours.size(); i++)
	{
		if (rooms[origin._neibhours[i]]._connected == false)
			dps(rooms, rooms[origin._neibhours[i]]);
	}
}


Dungeon::~Dungeon()
{
}
