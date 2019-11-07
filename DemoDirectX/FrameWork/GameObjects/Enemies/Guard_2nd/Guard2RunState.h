#pragma once
#include "Guard2State.h"
#include "Guard2.h"
#include "Guard2BeatenState.h"
#include "Guard2BurnedState.h"
#include "Guard2CutState.h"
#include "Guard2DartState.h"
#include "Guard2ArouseState.h"

class Guard2RunState :public Guard2State
{
public:
	Guard2RunState(Guard2Data *guard2Data);

	~Guard2RunState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	Guard2State::StateName GetState();

protected:

};

