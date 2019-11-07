#include "Guard3BeatenState.h"

Guard3BeatenState::Guard3BeatenState(Guard3Data * guard3Data)
{
	this->mGuard3Data = guard3Data;
	mGuard3Data->guard3->SetVy(0);
	mGuard3Data->guard3->SetVx(0);
}

Guard3BeatenState::~Guard3BeatenState()
{
}

void Guard3BeatenState::Update(float dt)
{
	if (this->mGuard3Data->guard3->GetCurrentAnimation()->mCurrentIndex == this->mGuard3Data->guard3->GetCurrentAnimation()->mTotalFrame)
		isDone = true;
	if (this->mGuard3Data->guard3->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mGuard3Data->guard3->SetState(new Guard3StandState(mGuard3Data));
	}
}

void Guard3BeatenState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mGuard3Data->guard3->GetTimeImmortal() <= 0)
		{
			mGuard3Data->guard3->TakeDamage(1);
			mGuard3Data->guard3->SetTimeImmortal(0.5);
		}
		break;
	case Entity::EntityTypes::Aladdin:
		if (this->mGuard3Data->guard3->mPlayer->IsMakeDamage() == true && this->mGuard3Data->guard3->GetTimeImmortal() <= 0)
		{
			if (GameCollision::isCollide(impactor->GetBoundWeapon(), mGuard3Data->guard3->GetBound()) == true)
			{
				mGuard3Data->guard3->TakeDamage(1);
				mGuard3Data->guard3->SetTimeImmortal(1);
			}
			mGuard3Data->guard3->SetState(new Guard3BeatenState(mGuard3Data));
		}
		break;
	}
}

Guard3State::StateName Guard3BeatenState::GetState()
{
	return Guard3State::Beaten;
}
