#pragma once
#include "Guard2State.h"
#include "Guard2.h"
#include "Guard2BeatenState.h"
#include "Guard2BurnedState.h"
#include "Guard2ArouseState.h"
#include "Guard2DartState.h"
#include "Guard2RunState.h"

class Guard2CutState :public Guard2State
{
public:
	Guard2CutState(Guard2Data *guard2Data);

	~Guard2CutState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard2State::StateName GetState();

protected:
	bool isDone = false;
};

