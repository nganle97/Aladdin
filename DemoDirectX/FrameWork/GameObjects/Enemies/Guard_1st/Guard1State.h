#pragma once
#include "Guard1Data.h"
#include "../../Entity.h"
#include <map>

class Guard1State
{
public:
	enum StateName
	{
		Run,
		Beat,
		Beaten,
		Stand
	};

	~Guard1State();

virtual void Update(float dt);

	//side va cham voi player
	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);



	virtual StateName GetState() = 0;

protected:
	Guard1State(Guard1Data *guard1Data);
	Guard1State();

	Guard1Data * mGuard1Data;
};