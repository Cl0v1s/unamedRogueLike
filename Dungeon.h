#pragma once
class Dungeon
{
private:
	int** _map;
	unsigned int _width;
	unsigned int _height;
public:
	Dungeon();
	~Dungeon();
};

