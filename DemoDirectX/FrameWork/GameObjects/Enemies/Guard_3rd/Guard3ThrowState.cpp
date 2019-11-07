#include "Guard3ThrowState.h"

Guard3ThrowState::Guard3ThrowState(Guard3Data * guard3Data)
{
	this->mGuard3Data = guard3Data;
	mGuard3Data->guard3->SetVx(0);
	mGuard3Data->guard3->SetVy(0);
	if (this->mGuard3Data->guard3->getFaceDirection() == Entity::FaceDirection::LEFT)
	{
		this->mGuard3Data->guard3->SetReverse(false);
	}
	else this->mGuard3Data->guard3->SetReverse(true);
}

Guard3ThrowState::~Guard3ThrowState()
{
}

void Guard3ThrowState::Update(float dt)
{
	if (this->mGuard3Data->guard3->GetCurrentAnimation()->mCurrentIndex == 3&&isThrow==true)
	{
		Entity* tmp = nullptr;
		if (this->mGuard3Data->guard3->getFaceDirection() == Entity::FaceDirection::LEFT)
		{
			tmp = new Guard3Weapon(this->mGuard3Data->guard3->GetBound().left, this->mGuard3Data->guard3->GetBound().top+20, D3DXVECTOR2(-100.0f, 5.0f), D3DXVECTOR2(-1.0f, 0.4f));
		}
		else
		{
			tmp = new Guard3Weapon(this->mGuard3Data->guard3->GetBound().right, this->mGuard3Data->guard3->GetBound().top+20, D3DXVECTOR2(100.0f, 5.0f), D3DXVECTOR2(1.0f, 0.4f));
		}
		mGuard3Data->guard3->getGameMap()->InsertWeapon(tmp);
		isThrow = false;
	}
	if (this->mGuard3Data->guard3->GetCurrentAnimation()->mCurrentIndex == 1&&isThrow==false)
	{
		this->mGuard3Data->guard3->SetState(new Guard3StandState(mGuard3Data));
		return;
	}

	
}

void Guard3ThrowState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mGuard3Data->guard3->GetTimeImmortal() <= 0)
		{
			mGuard3Data->guard3->SetState(new Guard3BeatenState(mGuard3Data));
			Sound::getInstance()->play("GuardPants", false, 1);
		}
		break;
	case Entity::EntityTypes::Aladdin:
		if (this->mGuard3Data->guard3->mPlayer->IsMakeDamage() == true && this->mGuard3Data->guard3->GetTimeImmortal() <= 0)
		{
			if (GameCollision::isCollide(impactor->GetBoundWeapon(), mGuard3Data->guard3->GetBound()) == true)
			{
				mGuard3Data->guard3->TakeDamage(1);
				mGuard3Data->guard3->SetTimeImmortal(1);
				mGuard3Data->guard3->SetState(new Guard3BeatenState(mGuard3Data));
				Sound::getInstance()->play("GuardPants", false, 1);
			}
		}
		break;
	}
}

Guard3State::StateName Guard3ThrowState::GetState()
{
	return Guard3State::Throw;
}
