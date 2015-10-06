#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdlib.h>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Const.h"

//d�finition des structures utiles � la g�n�ration
struct Room
{
	unsigned int _x;
	unsigned int _y;
	unsigned char _width;
	unsigned char _height;
	bool _connected;
	std::vector<Room*> _neibhours;
};

struct Point
{
	unsigned int _x;
	unsigned int _y;
};

class Dungeon
{
private:
	char** _map;
	unsigned int _width;
	unsigned int _height;
	sf::Texture* _tileset;
public:
	Dungeon();

	/// <summary>
	/// G�n�re les salles du donjon
	/// </summary>
	void generateRooms();

	/// <summary>
	/// G�n�re les couloirs entre les salles
	/// </summary>
	/// <param name="rooms">liste des salles</param>
	/// <param name="origin">Point de d�part de la g�n�ration de couloir</param>
	void generatePassages(std::vector<Room*> rooms, Room* origin);

	/// <summary>
	/// Creuse les couloirs dans la map
	/// </summary>
	/// <param name="from">Point de d�part du tunnel</param>
	/// <param name="to">Arriv� du tunnel</param>
	void dig(Room* from, Room* to);

	/// <summary>
	/// Trouve un point d'accroche  une salle
	/// </summary>
	/// <param name="room">Salle sur laquelle trouver le point d'acroche</param>
	/// <param name="point">Point contenant le point d'accroche</param>
	void getAnchorPoint(Room* room, Point &point);

	/// <summary>
	/// Algo de recherche en profondeur, parcours le donjon et indique quelles salles sont connect�es
	/// </summary>
	/// <param name="rooms">liste des salles</param>
	/// <param name="origin">Salle de d�part</param>
	void dfs(std::vector<Room*> &rooms, Room* origin);

	void generateWalls();

	/// <summary>
	/// Dessine la map
	/// </summary>
	/// <param name="render">Support de dessin</param>
	/// <param name="x">position x du canvas</param>
	/// <param name="y">position y du canvas</param>
	void draw(sf::RenderWindow* render, const unsigned int x, const unsigned int y);


	unsigned int getWidth() const;
	unsigned int getHeight() const;
	char getCellAt(const unsigned int x, const unsigned int y) const;

	~Dungeon();
};

#endif
