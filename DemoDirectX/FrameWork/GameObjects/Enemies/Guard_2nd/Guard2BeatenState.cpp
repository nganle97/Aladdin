#include "Guard2BeatenState.h"

Guard2BeatenState::Guard2BeatenState(Guard2Data * guard2Data)
{
	this->mGuard2Data = guard2Data;
	mGuard2Data->guard2->SetVy(0);
	mGuard2Data->guard2->SetVx(0);
}

Guard2BeatenState::~Guard2BeatenState()
{
}

void Guard2BeatenState::Update(float dt) //Chú ý điều kiện chuyển. Không thì sau khỉ Explore sẽ chuyển sang Cut
{
	if (mGuard2Data->guard2->GetCurrentAnimation()->mCurrentIndex == mGuard2Data->guard2->GetCurrentAnimation()->mTotalFrame)
	{
		isDone = true;
	}
	if (isDone == true && mGuard2Data->guard2->GetCurrentAnimation()->mCurrentIndex == 1)
		this->mGuard2Data->guard2->SetState(new Guard2CutState(mGuard2Data));
}

void Guard2BeatenState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mGuard2Data->guard2->GetTimeImmortal() <= 0)
		{
			mGuard2Data->guard2->TakeDamage(1);
			mGuard2Data->guard2->SetTimeImmortal(1);
			mGuard2Data->guard2->SetState(new Guard2BeatenState(mGuard2Data));
			Sound::getInstance()->play("GuardHit1", false, 1);
		}
		break;
	case Entity::EntityTypes::Aladdin:
		if (this->mGuard2Data->guard2->mPlayer->IsMakeDamage() == true && this->mGuard2Data->guard2->GetTimeImmortal() <= 0)
		{
			if (GameCollision::isCollide(mGuard2Data->guard2->mPlayer->GetBoundWeapon(), mGuard2Data->guard2->GetBoundBody()) == true)
			{
				mGuard2Data->guard2->TakeDamage(1);
				mGuard2Data->guard2->SetTimeImmortal(1);
				mGuard2Data->guard2->SetState(new Guard2BeatenState(mGuard2Data));
				Sound::getInstance()->play("GuardHit1", false, 1);
			}
		}
		break;
	}
}


Guard2State::StateName Guard2BeatenState::GetState()
{
	return Guard2State::Beaten;
}
