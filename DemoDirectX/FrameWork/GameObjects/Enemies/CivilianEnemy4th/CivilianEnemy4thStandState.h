#pragma once
#include "CivilianEnemy4thState.h"
#include "CivilianEnemy4th.h"
#include "CivilianEnemy4thBeatState.h"
#include "CivilianEnemy4thRunState.h"

class CivilianEnemy4thStandState :public CivilianEnemy4thState
{
public:
	CivilianEnemy4thStandState(CivilianEnemy4thData *civilianEnemy4thData);

	~CivilianEnemy4thStandState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data,Entity::SideCollisions side);

	CivilianEnemy4thState::StateName GetState();

protected:
	float timeStand = 0;
};
