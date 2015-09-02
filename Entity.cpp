#include "Entity.h"


Entity::Entity(int x, int y, unsigned int width, unsigned int height, std::string file)
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
	unsigned int frame = _frame; //on ne garde que la partie entière
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
