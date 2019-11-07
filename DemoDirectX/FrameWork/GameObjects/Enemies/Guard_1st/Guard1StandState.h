#pragma once
#include "Guard1State.h"
#include "Guard1.h"

class Guard1StandState :public Guard1State
{
public:
	Guard1StandState(Guard1Data *Guard1Data);

	~Guard1StandState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard1State::StateName GetState();

protected:

};

