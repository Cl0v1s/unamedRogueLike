#ifndef DAMAGE_H
#define DAMAGE_H

#include <string>

#include "EntityLiving.h"

class Damage
{
private:
	int _amount;
	std::string _animationFile;
	Entity* _origin;
public:
	Damage();

	int getAmount();
	void animate();
	virtual void impact(EntityLiving* target);

	~Damage();
};

#endif

