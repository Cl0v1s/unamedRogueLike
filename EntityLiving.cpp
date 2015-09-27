#include "EntityLiving.h"


EntityLiving::EntityLiving(const int x, const int y, const unsigned int width, const unsigned int height, const std::string file) : Entity(x,y,width,height, file)
{
	alive = true;
	sleeping = false;
	strain = 0;
	hunger = 0;
	stress = 0;
}

void EntityLiving::update()
{
	Entity::update();
	//calcul des stats
	//calcul de la fatigue
	if (!sleeping)
		strain += (100 / 1440) / 30; //100 en 24 heures
	else
		strain -= (100 / 360) / 30; //0 en 6 heures
	//calcul de a faim
	hunger += (100 / 720) / 30; //100 en 12 heures
	//calcul du stress
	if (hunger >= 100 || stress >= 100)
	{
		stress += (100 / 360) / 30; //100 en 6 heures
	}
	else
		stress = 0;
	//si l'entité est trop en manque, elle meurt
	if (stress >= 100)
	{
		alive = false;
	}
	//Application des limites
	if (strain > 100)
		strain = 100;
	if (strain <= 0)
	{
		sleeping = false;
		strain = 0;
	}
	if (hunger > 100)
		hunger = 100;
	if (hunger <= 0)
		hunger = 0;

}


void EntityLiving::eat()
{
	hunger = 0;
}

void EntityLiving::sleep()
{
	sleeping = true;
}

EntityLiving::~EntityLiving()
{
}
