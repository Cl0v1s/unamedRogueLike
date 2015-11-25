#include "Entity.h"


Entity::Entity(const unsigned int x, const unsigned int y, const Entity::Type type)
{
	//TODO: a coder
}

int Entity::getX() const
{
	return (int)_x;
}

int Entity::getY() const
{
	return (int)_y;
}

void Entity::setPos(const unsigned int x, const unsigned int y)
{
	_x = x;
	_y = y;
}

Entity::Type Entity::getType() const
{
	return _type;
}



Entity::~Entity()
{
}
