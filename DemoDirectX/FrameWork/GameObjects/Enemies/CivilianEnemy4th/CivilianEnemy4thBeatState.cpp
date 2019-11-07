#include "CivilianEnemy4thBeatState.h"

CivilianEnemy4thBeatState::CivilianEnemy4thBeatState(CivilianEnemy4thData * civilianEnemy4thData)
{
	this->mCivilianEnemy4thData = civilianEnemy4thData;
	this->mCivilianEnemy4thData->civilianEnemy4th->SetVy(0);
	this->mCivilianEnemy4thData->civilianEnemy4th->SetVx(0);
}

CivilianEnemy4thBeatState::~CivilianEnemy4thBeatState()
{
}

void CivilianEnemy4thBeatState::Update(float dt)
{
	if (this->mCivilianEnemy4thData->civilianEnemy4th->GetCurrentAnimation()->mCurrentIndex == 3 || this->mCivilianEnemy4thData->civilianEnemy4th->GetCurrentAnimation()->mCurrentIndex == 4)
		this->mCivilianEnemy4thData->civilianEnemy4th->SetMakeDamage(true);
	else
		this->mCivilianEnemy4thData->civilianEnemy4th->SetMakeDamage(false);


	if (this->mCivilianEnemy4thData->civilianEnemy4th->GetCurrentAnimation()->mCurrentIndex == this->mCivilianEnemy4thData->civilianEnemy4th->GetCurrentAnimation()->mTotalFrame)
		isDone = true;
	if (this->mCivilianEnemy4thData->civilianEnemy4th->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		if (this->mCivilianEnemy4thData->civilianEnemy4th->IsInAttackRange() == true)
		{
			return;
		}
		else this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thStandState(mCivilianEnemy4thData));
	}
}

void CivilianEnemy4thBeatState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
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
CivilianEnemy4thState::StateName CivilianEnemy4thBeatState::GetState()
{
	return CivilianEnemy4thState::Beat;
}
