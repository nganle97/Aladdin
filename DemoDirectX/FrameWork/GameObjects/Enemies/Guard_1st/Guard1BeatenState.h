#pragma once
#include "Guard1State.h"
#include "Guard1.h"
#include "Guard1BeatenState.h"
#include "Guard1BeatState.h"
#include "Guard1RunState.h"

class Guard1BeatenState :public Guard1State
{
public:
	Guard1BeatenState(Guard1Data *guard1Data);

	~Guard1BeatenState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard1State::StateName GetState();

protected:
	bool isDone = false;
};