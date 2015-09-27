#include "Entity.h"


Entity::Entity(const int x,const int y, const unsigned int width, const unsigned int height,const std::string file)
{
	_x = x; _y = y; _width = width; _height = height;
	if (!_texture.loadFromFile(file))
	{
		exit(1);
	}
	_sprite.setTexture(_texture);
}

void Entity::draw(sf::RenderWindow* render)
{
	//gestion de l'animation
	unsigned int frame = (unsigned int)_frame; //on ne garde que la partie entière
	_sprite.setTextureRect(sf::IntRect(frame*_width, 0, _width, _height));
	render->draw(_sprite);
}

void Entity::update()
{
	_frame++;
}

Entity::~Entity()
{
}
