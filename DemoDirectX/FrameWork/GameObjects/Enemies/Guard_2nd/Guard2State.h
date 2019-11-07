#pragma once
#include "Guard2Data.h"
#include "../../Entity.h"
#include <map>

class Guard2State
{
public:
	enum StateName
	{
		Arouse,
		Beaten,
		Burned,
		Cut,
		Dart,
		Run
	};

	~Guard2State();

	virtual void Update(float dt);

	//side va cham voi player
	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);



	virtual StateName GetState() = 0;

protected:
	Guard2State(Guard2Data *guard2Data);
	Guard2State();

	Guard2Data * mGuard2Data;
};