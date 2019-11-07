#pragma once
#include "Guard3Data.h"
#include "../../Entity.h"
#include <map>

class Guard3State
{
public:
	enum StateName
	{
		Dance,
		Beaten,
		Run,
		Stand,
		Throw
	};

	~Guard3State();

	virtual void Update(float dt);

	//side va cham voi player
	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);



	virtual StateName GetState() = 0;

protected:
	Guard3State(Guard3Data *guard3Data);
	Guard3State();

	Guard3Data * mGuard3Data;
};