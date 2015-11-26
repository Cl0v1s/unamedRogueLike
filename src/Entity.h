#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	static enum Type
	{
		//on r�pertorie ici la liste de tout les types d'entit�s
	};

protected:
	float _x;
	float _y;
	Entity::Type _type;
public:
	Entity(const unsigned int x, const unsigned int y, const Entity::Type type);
	
	/// <summary>
	/// Met � jour l'�tat de l'entit�
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// retourne la position X de l'entit�
	/// </summary>
	/// <returns></returns>
	int getX() const;

	/// <summary>
	/// Retourne la position y de l'entit�
	/// </summary>
	/// <returns></returns>
	int getY() const;

	/// <summary>
	/// Premet de changer la position de l'entit�
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setPos(const unsigned int x, const unsigned int y);
	
	/// <summary>
	/// Permet l'interraction des autres entit�s avec celle-ci
	/// </summary>
	virtual void interact(Entity *other) = 0;

	/// <summary>
	/// Retourne le type del'entit�
	/// </summary>
	/// <returns></returns>
	Entity::Type getType() const;
	
	~Entity();
};

#endif

