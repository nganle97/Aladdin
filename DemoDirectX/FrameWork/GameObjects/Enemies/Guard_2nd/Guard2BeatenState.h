#pragma once
#include "Guard2State.h"
#include "Guard2.h"
#include "Guard2RunState.h"
class Guard2BeatenState :public Guard2State
{
public:
	Guard2BeatenState(Guard2Data *guard3Data);

	~Guard2BeatenState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard2State::StateName GetState();

protected:

	bool isDone = false;
};
