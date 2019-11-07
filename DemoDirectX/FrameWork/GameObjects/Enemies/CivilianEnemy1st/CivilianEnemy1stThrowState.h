#pragma once
#include "CivilianEnemy1stState.h"
#include "CivilianEnemy1st.h"
#include "../../Weapon/CivilianEnemy1Weapon.h"
class CivilianEnemy1stThrowState :public CivilianEnemy1stState
{
public:
	CivilianEnemy1stThrowState(CivilianEnemy1stData *civilianEnemy1stData);

	~CivilianEnemy1stThrowState();

	void Update(float dt);

	//void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	CivilianEnemy1stState::StateName GetState();

protected:
	bool isThrow = false;
};
