#pragma once
#include "CivilianEnemy4thState.h"
#include "CivilianEnemy4th.h"
#include "CivilianEnemy4thBeatState.h"
#include "CivilianEnemy4thRunState.h"

class CivilianEnemy4thRunState :public CivilianEnemy4thState
{
public:
	CivilianEnemy4thRunState(CivilianEnemy4thData *civilianEnemy4thData);

	~CivilianEnemy4thRunState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	CivilianEnemy4thState::StateName GetState();

protected:
	float timeMove = 0;
};
