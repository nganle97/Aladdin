#pragma once
#include "Guard3State.h"
#include "Guard3.h"
#include "Guard3BeatenState.h"
#include "Guard3DanceState.h"
#include "Guard3ThrowState.h"
#include "Guard3RunState.h"

class Guard3StandState :public Guard3State
{
public:
	Guard3StandState(Guard3Data *guard3Data);

	~Guard3StandState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard3State::StateName GetState();

protected:

};

