#include "CivilianEnemy4thRunState.h"

CivilianEnemy4thRunState::CivilianEnemy4thRunState(CivilianEnemy4thData * civilianEnemy4thData)
{
	this->mCivilianEnemy4thData = civilianEnemy4thData;
	this->mCivilianEnemy4thData->civilianEnemy4th->SetVy(0);
	this->mCivilianEnemy4thData->civilianEnemy4th->SetVx(0);
}

CivilianEnemy4thRunState::~CivilianEnemy4thRunState()
{
}

void CivilianEnemy4thRunState::Update(float dt)
{
	if (timeMove >= 2)
	{
		timeMove = 0;
		this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thStandState(mCivilianEnemy4thData));
		return;
	}
	else timeMove += dt;
	if (this->mCivilianEnemy4thData->civilianEnemy4th->IsNearToPlayer() == true)
	{
		if (this->mCivilianEnemy4thData->civilianEnemy4th->getFaceDirection() == Entity::FaceDirection::LEFT)
			this->mCivilianEnemy4thData->civilianEnemy4th->SetVx(-mCivilianEnemy4thData->civilianEnemy4th->Vx);
		else
			this->mCivilianEnemy4thData->civilianEnemy4th->SetVx(mCivilianEnemy4thData->civilianEnemy4th->Vx);
	}
	else
	{
		this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thStandState(mCivilianEnemy4thData));
		return;
	}
	if (this->mCivilianEnemy4thData->civilianEnemy4th->IsInAttackRange() == true && this->mCivilianEnemy4thData->civilianEnemy4th->GetState() != CivilianEnemy4thState::Beat)
		this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thBeatState(mCivilianEnemy4thData));
}

void CivilianEnemy4thRunState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mCivilianEnemy4thData->civilianEnemy4th->GetTimeImmortal() <= 0)
		{
			mCivilianEnemy4thData->civilianEnemy4th->TakeDamage(1);
			mCivilianEnemy4thData->civilianEnemy4th->SetTimeImmortal(0.5);
		}
		break;
	case Entity::EntityTypes::Aladdin:
		if (this->mCivilianEnemy4thData->civilianEnemy4th->mPlayer->IsMakeDamage() == true && this->mCivilianEnemy4thData->civilianEnemy4th->GetTimeImmortal() <= 0)
		{
			mCivilianEnemy4thData->civilianEnemy4th->TakeDamage(1);
			mCivilianEnemy4thData->civilianEnemy4th->SetTimeImmortal(0.5);
		}
		break;
	}
}
CivilianEnemy4thState::StateName CivilianEnemy4thRunState::GetState()
{
	return CivilianEnemy4thState::Run;
}
