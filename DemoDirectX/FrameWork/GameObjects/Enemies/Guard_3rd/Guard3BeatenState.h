#pragma once
#include "Guard3State.h"
#include "Guard3.h"
#include "Guard3BeatenState.h"
#include "Guard3DanceState.h"
#include "Guard3RunState.h"
#include "Guard3StandState.h"
#include "../../Weapon/Guard3Weapon.h"
#include "../../Weapon//CivilianEnemy1Weapon.h"
#include "../../Weapon//JafarWeapon1.h"
class Guard3BeatenState :public Guard3State
{
public:
	Guard3BeatenState(Guard3Data *guard3Data);

	~Guard3BeatenState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Guard3State::StateName GetState();

protected:
	bool isThrow = true;
	bool isDone = false;
};
