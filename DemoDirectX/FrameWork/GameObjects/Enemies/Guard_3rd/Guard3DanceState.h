#pragma once
#include "Guard3State.h"
#include "Guard3.h"
#include "Guard3BeatenState.h"
#include "Guard3StandState.h"
#include "Guard3ThrowState.h"
#include "Guard3RunState.h"

class Guard3DanceState :public Guard3State
{
public:
	Guard3DanceState(Guard3Data *guard3Data);

	~Guard3DanceState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard3State::StateName GetState();

protected:

};

