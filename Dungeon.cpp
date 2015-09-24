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
			_map[i][u] = CELL_EMPTY; //normalisation de toutes les cases
		}
	}
	//chargement du tileset
	_tileset = new sf::Texture();
	if (!_tileset->loadFromFile("Assets/Tileset.png"))
	{
		std::cout << "ERROR: FILE NOT FOUND" << std::endl;
		exit(1);
	}
}

void Dungeon::generateRooms()
{
	//Création des salles
	std::vector<Room*> rooms;
	unsigned int rooms_number = rand() % (DUNGEON_ROOM_MAX - 2) + 2;
	for (unsigned int i = 0; i != rooms_number; i++)
	{
		Room* room = new Room();
		room->_width = rand() % (ROOM_WIDTH_MAX - 5) + 5;
		room->_height = rand() % (ROOM_HEIGHT_MAX - 5) + 5;
		room->_x = rand() % (_width - room->_width - 10) + 5;
		room->_y = rand() % (_height - room->_height- 10) + 5;

		//test de collision avec les autres salles
		bool error = false;
		unsigned int u = 0;
		while (u != rooms.size() && !error)
		{
			if (room->_x + room->_width >= rooms[u]->_x && room->_x <= rooms[u]->_x + rooms[u]->_width) //test de collision horizontal
			{
				if (room->_y + room->_height >= rooms[u]->_y && room->_y <= rooms[u]->_y + rooms[u]->_height)
				{
					error = true;
				}
			}
			u++;
		}

		//analyse des résultats
		if (!error)
		{
			//ajout de la salle à la liste
			rooms.push_back(room);
		}
	}
	//selection d'une salle au hasard de départ
	Room* start = rooms[rand() % rooms.size()];
	generatePassages(rooms, start);
	//applications des salles à la map et suppression de leur existence en mémoire
	for (unsigned int i = 0; i != rooms.size(); i++)
	{
		for (unsigned int x = 0; x != rooms[i]->_width; x++)
		{
			for (unsigned int y = 0; y != rooms[i]->_height; y++)
			{
				_map[x + rooms[i]->_x][y + rooms[i]->_y] = CELL_FLOOR;
			}
		}
		delete rooms[i];
	}


}

void Dungeon::generatePassages(std::vector<Room*> rooms, Room* origin)
{
	//on choisit un nombre de salles à parcourir
	unsigned int length = rand() % 3 + 1;
	//On choisit une liste de salle à parcourir
	std::vector<Room*> path;
	path.push_back(origin);
	for (unsigned int i = 0; i != length; i++)
	{
		path.push_back(rooms[rand() % rooms.size()]);
	}
	//Creusage des tunnels
	for (unsigned int i = 1; i != path.size(); i++)
	{
		//On indique aux salles qu'elles sont voisines
		path[i - 1]->_neibhours.push_back(path[i]);
		path[i]->_neibhours.push_back(path[i-1]);
		//On dessine le passage
		dig(path[i - 1], path[i]);
	}
	//on vérifie que toutes les salles sont reliées
	for (unsigned int i = 0; i != rooms.size(); i++)
		rooms[i]->_connected = false;
	dfs(rooms, origin);
	bool done = true;
	unsigned int i = 0;
	while (i != rooms.size() && done == true)
	{
		if (rooms[i]->_connected == false)
			done = false;
		else 
			i++;
	}
	if (!done)
	{
		//on utilise la salle non reliée trouvée ci-dessus
		origin = rooms[i];
		generatePassages(rooms, origin);
	}


}

void Dungeon::dig(Room* from, Room* to)
{
	Point current;
	Point target;
	getAnchorPoint(from, current);
	getAnchorPoint(to, target);
	while (current._x != target._x || current._y != target._y)
	{
		_map[current._x][current._y] = CELL_FLOOR;
		if (target._x > current._x)
			current._x += 1;
		else if (target._x < current._x)
			current._x -= 1;
		else if (target._y > current._y)
			current._y += 1;
		else if (target._y < current._y)
			current._y -= 1;
	}
}

void Dungeon::getAnchorPoint(Room* room, Point &point)
{
	unsigned int side = rand() % 4;
	switch (side)
	{
	case 0:
		point._x = room->_x;
		point._y = room->_y + rand() % (room->_height - 3) + 2;
		break;
	case 1:
		point._y = room->_y;
		point._x = room->_x + rand() % (room->_width - 3) + 2;
		break;
	case 2:
		point._x = room->_x+ room->_width -1 ;
		point._y = room->_y + rand() % (room->_height - 3) + 2;
		break;
	case 3:
		point._y = room->_y+room->_height - 1;
		point._x = room->_x + rand() % (room->_width - 3) + 2;
		break;
	}
}

void Dungeon::draw(sf::RenderWindow* render, const int x, const int y)
{
	sf::Sprite sprite;
	sf::IntRect rect;
	rect.top = 0;
	rect.width = 32;
	rect.height = 32;
	sprite.setTexture(*_tileset);
	for (int i = 0; i != DEVICE_WIDTH / 32; i++)
	{
		for (int u = 0; u != DEVICE_HEIGHT / 32; u++)
		{
			if ( i + x >= 0 && i + x < _width && u + y >= 0 && u + y < _height)
				rect.left = (_map[i+x][u+y]-1) * 32;
			if (rect.left >= 0)
			{
				sprite.setTextureRect(rect);
				sprite.setPosition(i * 32, u * 32);
				render->draw(sprite);
			}
			rect.left = -1;
		}
	}
}

void Dungeon::dfs(std::vector<Room*> &rooms, Room* origin)
{
	origin->_connected = true;
	for (unsigned int i = 0; i != origin->_neibhours.size(); i++)
	{
		if (origin->_neibhours[i]->_connected == false)
			dfs(rooms, origin->_neibhours[i]);
	}
}


Dungeon::~Dungeon()
{
}
