#pragma once
#include "Entity.h"
class EntityLiving :
	public Entity
{
private:
	int hunger;
	int strain;
	unsigned int stress;
	bool sleeping;
	bool alive;

public:
	EntityLiving(const int x, const int y, const unsigned int width, const unsigned int height, const std::string file);
	virtual void update();
	void eat();
	void sleep();
	virtual ~EntityLiving();
};

