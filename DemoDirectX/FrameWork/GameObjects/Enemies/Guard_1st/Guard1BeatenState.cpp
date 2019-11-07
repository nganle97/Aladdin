#include "Guard1BeatenState.h"
#include "Guard1StandState.h"

Guard1BeatenState::Guard1BeatenState(Guard1Data * guard1Data)
{
	this->mGuard1Data = guard1Data;
	mGuard1Data->guard1->SetVy(0);
	mGuard1Data->guard1->SetVx(0);
}

Guard1BeatenState::~Guard1BeatenState()
{
}

void Guard1BeatenState::Update(float dt)
{
	if (mGuard1Data->guard1->GetCurrentAnimation()->mCurrentIndex == mGuard1Data->guard1->GetCurrentAnimation()->mTotalFrame)
	{
		isDone = true;
	}
	if (isDone == true && mGuard1Data->guard1->GetCurrentAnimation()->mCurrentIndex == 1)
		this->mGuard1Data->guard1->SetState(new Guard1StandState(mGuard1Data));


}

void Guard1BeatenState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mGuard1Data->guard1->GetTimeImmortal() <= 0)
		{
			mGuard1Data->guard1->TakeDamage(1);
			mGuard1Data->guard1->SetTimeImmortal(1);
		}
		break;
	case Entity::EntityTypes::Aladdin:
		if (this->mGuard1Data->guard1->mPlayer->IsMakeDamage()==true&& this->mGuard1Data->guard1->GetTimeImmortal() <= 0 )
		{
			if (GameCollision::isCollide(mGuard1Data->guard1->mPlayer->GetBoundWeapon(), mGuard1Data->guard1->GetBoundBody()) == true)
			{
				mGuard1Data->guard1->TakeDamage(1);
				mGuard1Data->guard1->SetTimeImmortal(1);
			}
		}
		break;
	}
}

Guard1State::StateName Guard1BeatenState::GetState()
{
	return Guard1State::Beaten;
}

