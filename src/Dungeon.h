#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <vector>

#include "Helper.h"
#include "Entity.h"

class Biome;

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
	std::vector<Biome*> _biomes;
	std::vector<Entity*> _entities;
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

	/// <summary>
	/// Génère les murs du donjon
	/// </summary>
	void generateWalls();

	/// <summary>
	/// Met à jour les élements du donjon
	/// </summary>
	void update();

	/// <summary>
	/// retourne la carte du donjon
	/// </summary>
	char** getMap() const;

	/// <summary>
	/// Permet de changer la valeur d'un cellule de la map
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="value"></param>
	/// <returns></returns>
	void setCellAt(const unsigned int x,const unsigned  int y, char value);

	/// <summary>
	/// retourne la largeur de la carte du donjon
	/// </summary>
	/// <returns></returns>
	unsigned int getWidth() const;

	/// <summary>
	/// Retourne la hauteur de la carte du donjon
	/// </summary>
	/// <returns></returns>
	unsigned int getHeight() const;

	/// <summary>
	/// Recupère la valeur de la cellule àa la position donnée
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	char getCellAt(const unsigned int x, const unsigned int y) const;

	//TODO: à coder
	void applyBiomes();

	~Dungeon();
};

#endif
