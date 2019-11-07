#include "CivilianEnemy2ndThrowState.h"
#include "../../Weapon/Guard3Weapon.h"

CivilianEnemy2ndThrowState::CivilianEnemy2ndThrowState(CivilianEnemy2ndData * civilianEnemy2ndData)
{
	this->mCivilianEnemy2ndData = civilianEnemy2ndData;
}

CivilianEnemy2ndThrowState::~CivilianEnemy2ndThrowState()
{
}

void CivilianEnemy2ndThrowState::Update(float dt)
{
	if (this->mCivilianEnemy2ndData->civilianEnemy2nd->mPlayer->GetPosition().x - this->mCivilianEnemy2ndData->civilianEnemy2nd->GetPosition().x > 0)
	{
		mCivilianEnemy2ndData->civilianEnemy2nd->SetReverse(false);
		this->mCivilianEnemy2ndData->civilianEnemy2nd->faceDirection = Entity::FaceDirection::RIGHT;

	}
	else
	{
		this->mCivilianEnemy2ndData->civilianEnemy2nd->faceDirection = Entity::FaceDirection::LEFT;
		mCivilianEnemy2ndData->civilianEnemy2nd->SetReverse(true);
	}
	if (this->mCivilianEnemy2ndData->civilianEnemy2nd->IsNearToPlayer()==true)
	if (this->mCivilianEnemy2ndData->civilianEnemy2nd->GetCurrentAnimation()->mCurrentIndex == 10&&isThrow==true)
	{
		Entity* tmp = nullptr;
		if (this->mCivilianEnemy2ndData->civilianEnemy2nd->getFaceDirection() == Entity::FaceDirection::LEFT)
		{
			if (abs(this->mCivilianEnemy2ndData->civilianEnemy2nd->mPlayer->GetPosition().x-this->mCivilianEnemy2ndData->civilianEnemy2nd->GetPosition().x)>150)
			tmp = new Guard3Weapon(this->mCivilianEnemy2ndData->civilianEnemy2nd->GetBound().left, this->mCivilianEnemy2ndData->civilianEnemy2nd->GetBound().top,D3DXVECTOR2(-70.0f,Define::PLAYER_MIN_JUMP_VELOCITY*1.6),D3DXVECTOR2(0,4.0f));
			else
				tmp = new Guard3Weapon(this->mCivilianEnemy2ndData->civilianEnemy2nd->GetBound().left, this->mCivilianEnemy2ndData->civilianEnemy2nd->GetBound().top+35, D3DXVECTOR2(-100.0f, 40.0f), D3DXVECTOR2(0, 0));
		}
		else
		{
			if (abs(this->mCivilianEnemy2ndData->civilianEnemy2nd->mPlayer->GetPosition().x - this->mCivilianEnemy2ndData->civilianEnemy2nd->GetPosition().x)>150)

			tmp = new Guard3Weapon(this->mCivilianEnemy2ndData->civilianEnemy2nd->GetBound().right, this->mCivilianEnemy2ndData->civilianEnemy2nd->GetBound().top, D3DXVECTOR2(70.0f, Define::PLAYER_MIN_JUMP_VELOCITY*1.6), D3DXVECTOR2(0, 4.0f));
			else
				tmp = new Guard3Weapon(this->mCivilianEnemy2ndData->civilianEnemy2nd->GetBound().right, this->mCivilianEnemy2ndData->civilianEnemy2nd->GetBound().top+35, D3DXVECTOR2(100.0f, 40.0f), D3DXVECTOR2(0, 0));

		}

		mCivilianEnemy2ndData->civilianEnemy2nd->getGameMap()->InsertWeapon(tmp);
		isThrow = false;
	}
	else if (this->mCivilianEnemy2ndData->civilianEnemy2nd->GetCurrentAnimation()->mCurrentIndex == 1)
	{
		isThrow = true;
	}
}

CivilianEnemy2ndState::StateName CivilianEnemy2ndThrowState::GetState()
{
	return CivilianEnemy2ndState::Throw;
}
