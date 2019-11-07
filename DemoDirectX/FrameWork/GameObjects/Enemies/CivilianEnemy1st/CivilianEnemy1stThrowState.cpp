#include "CivilianEnemy1stThrowState.h"

CivilianEnemy1stThrowState::CivilianEnemy1stThrowState(CivilianEnemy1stData * civilianEnemy1stData)
{
	this->mCivilianEnemy1stData = civilianEnemy1stData;
}

CivilianEnemy1stThrowState::~CivilianEnemy1stThrowState()
{
}

void CivilianEnemy1stThrowState::Update(float dt)
{
	if (this->mCivilianEnemy1stData->civilianEnemy1st->GetCurrentAnimation()->mCurrentIndex == 8 && isThrow == true)
	{
		Entity* tmp = nullptr;
		if (this->mCivilianEnemy1stData->civilianEnemy1st->getFaceDirection() == Entity::FaceDirection::LEFT)
		{
			tmp = new CivilianEnemy1Weapon(D3DXVECTOR2(this->mCivilianEnemy1stData->civilianEnemy1st->GetBound().right+8, this->mCivilianEnemy1stData->civilianEnemy1st->GetBound().bottom+21));
		
		}
		else
		{
			tmp = new CivilianEnemy1Weapon(D3DXVECTOR2(this->mCivilianEnemy1stData->civilianEnemy1st->GetBound().right+8, this->mCivilianEnemy1stData->civilianEnemy1st->GetBound().bottom+21));
			
		}
		tmp->SetVx(0.0f);

		mCivilianEnemy1stData->civilianEnemy1st->getGameMap()->InsertWeapon(tmp);
		isThrow = false;
	}
	else if (this->mCivilianEnemy1stData->civilianEnemy1st->GetCurrentAnimation()->mCurrentIndex == 1)
	{
		isThrow = true;
	}
}

CivilianEnemy1stState::StateName CivilianEnemy1stThrowState::GetState()
{
	return CivilianEnemy1stState::Throw;
}
