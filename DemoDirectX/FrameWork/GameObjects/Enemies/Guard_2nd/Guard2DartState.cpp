#include "Guard2DartState.h"

Guard2DartState::Guard2DartState(Guard2Data * guard2Data)
{
	this->mGuard2Data = guard2Data;
	mGuard2Data->guard2->SetVy(0);
	mGuard2Data->guard2->SetVx(0);
}

Guard2DartState::~Guard2DartState()
{
}

void Guard2DartState::Update(float dt)
{
	if (this->mGuard2Data->guard2->GetCurrentAnimation()->mCurrentIndex == 5 || this->mGuard2Data->guard2->GetCurrentAnimation()->mCurrentIndex == 6)
		this->mGuard2Data->guard2->SetMakeDamage(true);
	else
		this->mGuard2Data->guard2->SetMakeDamage(false);


	if (this->mGuard2Data->guard2->GetCurrentAnimation()->mCurrentIndex == this->mGuard2Data->guard2->GetCurrentAnimation()->mTotalFrame)
		isDone = true;
	if (this->mGuard2Data->guard2->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		if (this->mGuard2Data->guard2->IsInAttackRange() == true)
		{
			int tmp = rand() % 2;
			if (tmp == 0) this->mGuard2Data->guard2->SetState(new Guard2CutState(mGuard2Data));
		}
		else this->mGuard2Data->guard2->SetState(new Guard2ArouseState(mGuard2Data));
	}
}

void Guard2DartState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
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
				return;
			}
		}
		if (this->mGuard2Data->guard2->IsMakeDamage() == true && this->mGuard2Data->guard2->mPlayer->GetTimeImmortal() <= 0)
		{
			if (GameCollision::isCollide(mGuard2Data->guard2->mPlayer->GetBoundBody(), mGuard2Data->guard2->GetBoundWeapon()) == true)
			{
				mGuard2Data->guard2->mPlayer->TakeDamage(1);
				mGuard2Data->guard2->mPlayer->SetTimeImmortal(1.8);
			}
		}
		break;
	}
}


Guard2State::StateName Guard2DartState::GetState()
{
	return Guard2State::Dart;
}