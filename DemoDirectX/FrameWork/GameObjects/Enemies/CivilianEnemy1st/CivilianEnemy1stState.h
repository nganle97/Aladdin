#pragma once
#include "CivilianEnemy1stData.h"
#include "../../Entity.h"

class CivilianEnemy1stState
{
public:
	enum StateName
	{
		Throw
	};
	~CivilianEnemy1stState();

	virtual void Update(float dt);

	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	
	virtual StateName GetState() = 0;

protected:
	CivilianEnemy1stState(CivilianEnemy1stData *civilianEnemy1stData);
	CivilianEnemy1stState();

	CivilianEnemy1stData *mCivilianEnemy1stData;
};