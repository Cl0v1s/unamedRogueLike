#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class Scene
{
public:
	Scene();
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* render) = 0;
	virtual ~Scene();

	static void Change(Scene* &current, Scene* next);
	static void Delete(Scene* current);
};

#endif

