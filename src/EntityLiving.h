#ifndef ENTITYLIVING_H
#define ENTITYLIVING_H

#include <math.h>

#include "Helper.h"
#include "Entity.h"
#include "Vector.h"

class EntityLiving : Entity
{
private:
	int _life;
	Vector _velocity;
	float _defense;
public:
	EntityLiving(const unsigned int x, const unsigned int y, const Entity::Type type);
	
	int getLife();
	bool isAlive();
	void setVelocity(const float x, const float y);
	void moveTo(const int x, const int y);
	void hurt(const Damage* damage);
	float getDefense();
	virtual void update();
	virtual void interact(Entity *other);
	
	~EntityLiving();
};

#endif