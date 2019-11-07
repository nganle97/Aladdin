#pragma once
#pragma once
#include "CivilianEnemy2ndData.h"
#include "../../Entity.h"

class CivilianEnemy2ndState
{
public:
	enum StateName
	{
		Throw
	};
	~CivilianEnemy2ndState();

	virtual void Update(float dt);

	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState() = 0;

protected:
	CivilianEnemy2ndState(CivilianEnemy2ndData *civilianEnemy2ndData);
	CivilianEnemy2ndState();

	CivilianEnemy2ndData *mCivilianEnemy2ndData;
};