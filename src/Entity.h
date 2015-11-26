#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	static enum Type
	{
		//on répertorie ici la liste de tout les types d'entités
	};

protected:
	float _x;
	float _y;
	Entity::Type _type;
public:
	Entity(const unsigned int x, const unsigned int y, const Entity::Type type);
	
	/// <summary>
	/// Met à jour l'état de l'entité
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// retourne la position X de l'entité
	/// </summary>
	/// <returns></returns>
	int getX() const;

	/// <summary>
	/// Retourne la position y de l'entité
	/// </summary>
	/// <returns></returns>
	int getY() const;

	/// <summary>
	/// Premet de changer la position de l'entité
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setPos(const unsigned int x, const unsigned int y);
	
	/// <summary>
	/// Permet l'interraction des autres entités avec celle-ci
	/// </summary>
	virtual void interact(Entity *other) = 0;

	/// <summary>
	/// Retourne le type del'entité
	/// </summary>
	/// <returns></returns>
	Entity::Type getType() const;
	
	~Entity();
};

#endif

