#pragma once
#include "Guard1State.h"
#include "Guard1.h"
#include "Guard1BeatenState.h"
#include "Guard1RunState.h"

class Guard1BeatState :public Guard1State
{
public:
	Guard1BeatState(Guard1Data *guard1Data);

	~Guard1BeatState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard1State::StateName GetState();

protected:
	bool IsInAttackRange();
	bool isDone = false;
};