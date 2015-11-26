#include "EntityLiving.h"


EntityLiving::EntityLiving(const unsigned int x, const unsigned int y, const Entity::Type type) : Entity(x,y,type)
{
}

int EntityLiving::getLife()
{
	return _life;
}

bool EntityLiving::isAlive()
{
	return _life > 0;
}

float EntityLiving::getDefense()
{
	return _defense;
}

void EntityLiving::update()
{

	_x += DELTA * _velocity.x;
	_y += DELTA * _velocity.y;
}

void EntityLiving::interact(Entity *other)
{
	//TODO: à faire
}

void EntityLiving::hurt(const Damage* damage)
{
	//TODO: à faire
}

void EntityLiving::moveTo(const int x, const int y)
{
	_velocity.x = _x - x;
	_velocity.y = _y - y;
}

void EntityLiving::setVelocity(const float x, const float y)
{
	_velocity.x = x;
	_velocity.y = y;
}



EntityLiving::~EntityLiving()
{
}
