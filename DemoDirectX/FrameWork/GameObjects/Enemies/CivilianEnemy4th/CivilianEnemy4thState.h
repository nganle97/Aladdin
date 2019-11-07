#pragma once
#pragma once
#include "CivilianEnemy4thData.h"
#include "../../Entity.h"

class CivilianEnemy4thState
{
public:
	enum StateName
	{
		Stand,
		Beat,
		Run
	};
	~CivilianEnemy4thState();

	virtual void Update(float dt);

	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	virtual StateName GetState() = 0;

protected:
	CivilianEnemy4thState(CivilianEnemy4thData *civilianEnemy4thData);
	CivilianEnemy4thState();

	CivilianEnemy4thData *mCivilianEnemy4thData;
};