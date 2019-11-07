#pragma once
#include "Guard2State.h"
#include "Guard2.h"
#include "Guard2BeatenState.h"
#include "Guard2BurnedState.h"
#include "Guard2CutState.h"
#include "Guard2DartState.h"
#include "Guard2RunState.h"

class Guard2ArouseState :public Guard2State
{
public:
	Guard2ArouseState(Guard2Data *guard2Data);

	~Guard2ArouseState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard2State::StateName GetState();

protected:

};

