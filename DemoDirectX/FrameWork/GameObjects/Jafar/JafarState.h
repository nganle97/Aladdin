#pragma once
#include "JafarData.h"
#include "../Entity.h"
#include <map>

class JafarState
{
public:
	enum StateName
	{
		Original,
		Snake
	};
	~JafarState();
	virtual void Update(float dt);

	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	
	virtual StateName GetState() = 0;

protected:
	JafarState(JafarData *jafarData);
	JafarState();

	JafarData *mJafarData;

};