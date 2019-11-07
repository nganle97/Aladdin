#include "CivilianEnemy2ndState.h"

CivilianEnemy2ndState::~CivilianEnemy2ndState()
{
}

void CivilianEnemy2ndState::Update(float dt)
{
}

void CivilianEnemy2ndState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

CivilianEnemy2ndState::CivilianEnemy2ndState(CivilianEnemy2ndData * civilianEnemy2ndData)
{
	this->mCivilianEnemy2ndData = civilianEnemy2ndData;
}

CivilianEnemy2ndState::CivilianEnemy2ndState()
{
}
