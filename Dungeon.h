#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdlib.h>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Const.h"

//définition des structures utiles à la génération
struct Room
{
	unsigned int _x;
	unsigned int _y;
	unsigned char _width;
	unsigned char _height;
	bool _connected;
	std::vector<int> _neibhours;
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
	/// Génère les salles du donjon
	/// </summary>
	void generateRooms();

	/// <summary>
	/// Génère les couloirs donjon
	/// </summary>
	void generatePassages(std::vector<Room> &rooms);

	/// <summary>
	/// génère un chemin (ensemble de pls couloirs) entre n salles
	/// </summary>
	/// <param name="rooms">Graphes des salles</param>
	/// <param name="origin">Salle de départ du chemin</param>
	void makePath(std::vector<Room> &rooms, Room &origin);

	/// <summary>
	/// Cherche un point d'encrage à un chemin dans une salle
	/// </summary>
	/// <param name="room">Salle dans laquelle chercher un point d'ancrage</param>
	/// <param name="anchor">Référence vers le point à modifier</param>
	void searchAnchorPoint(Room &room, Point &anchor);

	/// <summary>
	/// On teste si toutes les salles sont connectés
	/// </summary>
	/// <param name="rooms">Graphe des salles</param>
	/// <param name="origin">Salle de départ</param>
	void dps(std::vector<Room> &rooms, Room &origin);

	/// <summary>
	/// Dessine la map
	/// </summary>
	/// <param name="render">Support de dessin</param>
	/// <param name="x">position x du canvas</param>
	/// <param name="y">position y du canvas</param>
	void draw(sf::RenderWindow* render, const int x, const int y);


	~Dungeon();
};

#endif

