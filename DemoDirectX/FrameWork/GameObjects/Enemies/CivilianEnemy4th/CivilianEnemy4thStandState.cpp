#include "CivilianEnemy4thStandState.h"

CivilianEnemy4thStandState::CivilianEnemy4thStandState(CivilianEnemy4thData * civilianEnemy4thData)
{
	this->mCivilianEnemy4thData = civilianEnemy4thData;
	this->mCivilianEnemy4thData->civilianEnemy4th->SetVy(0);
	this->mCivilianEnemy4thData->civilianEnemy4th->SetVx(0);
}

CivilianEnemy4thStandState::~CivilianEnemy4thStandState()
{
}

void CivilianEnemy4thStandState::Update(float dt)
{
	if (this->mCivilianEnemy4thData->civilianEnemy4th->IsInAttackRange() == true)
	{
		if (this->GetState() != CivilianEnemy4thState::Beat)
		{
			this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thBeatState(mCivilianEnemy4thData));
			return;
		}
	}
	else if (this->mCivilianEnemy4thData->civilianEnemy4th->IsNearToPlayer() == true)
	{
		if (this->GetState() != CivilianEnemy4thState::Run)
		{
			if (timeStand >= 2.5)
			{
				timeStand = 0;
				this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thRunState(mCivilianEnemy4thData));
				return;
			}
			else timeStand += dt;
		}
	}

}

void CivilianEnemy4thStandState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (this->mCivilianEnemy4thData->civilianEnemy4th->GetCurrentAnimation()->mCurrentIndex>=5)
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

CivilianEnemy4thState::StateName CivilianEnemy4thStandState::GetState()
{
	return CivilianEnemy4thState::Stand;
}
