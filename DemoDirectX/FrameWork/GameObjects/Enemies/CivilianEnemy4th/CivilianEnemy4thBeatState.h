#pragma once
#include "CivilianEnemy4thState.h"
#include "CivilianEnemy4th.h"
#include "CivilianEnemy4thStandState.h"
#include "CivilianEnemy4thBeatState.h"

class CivilianEnemy4thBeatState :public CivilianEnemy4thState
{
public:
	CivilianEnemy4thBeatState(CivilianEnemy4thData *civilianEnemy4thData);

	~CivilianEnemy4thBeatState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	CivilianEnemy4thState::StateName GetState();

protected:
	bool isDone = false;
};
