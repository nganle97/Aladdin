#pragma once
#include "Guard3State.h"
#include "Guard3.h"
#include "Guard3BeatenState.h"
#include "Guard3DanceState.h"
#include "Guard3ThrowState.h"
#include "Guard3StandState.h"

class Guard3RunState :public Guard3State
{
public:
	Guard3RunState(Guard3Data *guard3Data);

	~Guard3RunState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard3State::StateName GetState();

protected:
	float Vx;
};
