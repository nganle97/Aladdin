#include "CivilianEnemy1stState.h"

CivilianEnemy1stState::~CivilianEnemy1stState()
{
}

void CivilianEnemy1stState::Update(float dt)
{
}

void CivilianEnemy1stState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

CivilianEnemy1stState::CivilianEnemy1stState(CivilianEnemy1stData * civilianEnemy1stData)
{
	this->mCivilianEnemy1stData = civilianEnemy1stData;
}

CivilianEnemy1stState::CivilianEnemy1stState()
{
}
