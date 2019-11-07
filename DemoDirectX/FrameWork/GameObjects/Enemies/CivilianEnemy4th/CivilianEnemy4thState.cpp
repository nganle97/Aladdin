#include "CivilianEnemy4thState.h"

CivilianEnemy4thState::~CivilianEnemy4thState()
{
}

void CivilianEnemy4thState::Update(float dt)
{
}

void CivilianEnemy4thState::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}

CivilianEnemy4thState::CivilianEnemy4thState(CivilianEnemy4thData * civilianEnemy4thData)
{
	this->mCivilianEnemy4thData = civilianEnemy4thData;
}

CivilianEnemy4thState::CivilianEnemy4thState()
{
}
