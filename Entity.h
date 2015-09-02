#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	//variables de position
	int _x;
	int _y;
	//variable de taille
	unsigned int _width;
	unsigned int _height;
	//variables graphiques
	std::string _file;
	float _frame;
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
public:
	Entity(int x, int y, unsigned int width, unsigned int height, std::string file);
	virtual void draw(sf::RenderWindow* render);
	virtual void update();
	virtual ~Entity();
};

#endif

