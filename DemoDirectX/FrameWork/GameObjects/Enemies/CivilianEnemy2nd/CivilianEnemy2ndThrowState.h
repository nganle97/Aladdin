#pragma once
#include "CivilianEnemy2ndState.h"
#include "CivilianEnemy2nd.h"

class CivilianEnemy2ndThrowState :public CivilianEnemy2ndState
{
public:
	CivilianEnemy2ndThrowState(CivilianEnemy2ndData *civilianEnemy2ndData);

	~CivilianEnemy2ndThrowState();

	void Update(float dt);

	//void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	CivilianEnemy2ndState::StateName GetState();

protected:
	bool isThrow = true;
};
