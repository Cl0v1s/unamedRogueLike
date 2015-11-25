#ifndef BIOME_H
#define BIOME_H

#include <vector>

#include "Entity.h"

class Dungeon;

class Biome
{
private: 
	std::vector<Entity::Type> _possibleSpawn;

public:
	Biome();
	void apply(Dungeon* dungeon);
	~Biome();
};

#endif

