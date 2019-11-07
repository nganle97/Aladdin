#pragma once
#include "Guard1State.h"
#include "Guard1.h"
#include "Guard1BeatenState.h"
#include "Guard1BeatState.h"

class Guard1RunState :public Guard1State
{
public:
	Guard1RunState(Guard1Data *guard1Data);
	
	~Guard1RunState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	

	Guard1State::StateName GetState();

protected:

};