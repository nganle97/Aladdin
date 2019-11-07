#include "Guard1BeatState.h"
#include "Guard1StandState.h"
Guard1BeatState::Guard1BeatState(Guard1Data * guard1Data)
{
	this->mGuard1Data = guard1Data;
	mGuard1Data->guard1->SetVx(0);
	mGuard1Data->guard1->SetVy(0);
}

Guard1BeatState::~Guard1BeatState()
{
}

void Guard1BeatState::Update(float dt)
{
	if (this->mGuard1Data->guard1->GetCurrentAnimation()->mCurrentIndex == 3 || this->mGuard1Data->guard1->GetCurrentAnimation()->mCurrentIndex == 4)
		this->mGuard1Data->guard1->SetMakeDamage(true);
	else
		this->mGuard1Data->guard1->SetMakeDamage(false);


	if (this->mGuard1Data->guard1->GetCurrentAnimation()->mCurrentIndex == this->mGuard1Data->guard1->GetCurrentAnimation()->mTotalFrame)
		isDone = true;
	if (this->mGuard1Data->guard1->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		if (this->mGuard1Data->guard1->IsInAttackRange() == true)
		{
			return;
		}
		else this->mGuard1Data->guard1->SetState(new Guard1StandState(mGuard1Data));
	}

}

void Guard1BeatState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mGuard1Data->guard1->GetTimeImmortal() <= 0)
		{
			mGuard1Data->guard1->TakeDamage(1);
			mGuard1Data->guard1->SetTimeImmortal(1);
			mGuard1Data->guard1->SetState(new Guard1BeatenState(mGuard1Data));
		}
		break;
	case Entity::EntityTypes::Aladdin:
		if (this->mGuard1Data->guard1->mPlayer->IsMakeDamage() == true&&this->mGuard1Data->guard1->GetTimeImmortal() <= 0)
		{
			if (GameCollision::isCollide(mGuard1Data->guard1->mPlayer->GetBoundWeapon(), mGuard1Data->guard1->GetBoundBody()) == true)
			{
				mGuard1Data->guard1->TakeDamage(1);
				mGuard1Data->guard1->SetTimeImmortal(1);
				mGuard1Data->guard1->SetState(new Guard1BeatenState(mGuard1Data));
				Sound::getInstance()->play("GuardHit1", false, 1);
			}
			
			return;
		}
		if (this->mGuard1Data->guard1->IsMakeDamage() == true && this->mGuard1Data->guard1->mPlayer->GetTimeImmortal() <= 0)
		{
			if (GameCollision::isCollide(mGuard1Data->guard1->mPlayer->GetBoundBody(), mGuard1Data->guard1->GetBoundWeapon()) == true)
			{
				mGuard1Data->guard1->mPlayer->TakeDamage(1);
				mGuard1Data->guard1->mPlayer->SetTimeImmortal(1.8);
			}
		}
		break;
	}
}

bool Guard1BeatState::IsInAttackRange()
{
	int deltaX = abs(this->mGuard1Data->guard1->mPlayer->GetPosition().x - this->mGuard1Data->guard1->GetPosition().x);
	int deltaY = abs(this->mGuard1Data->guard1->mPlayer->GetPosition().y - this->mGuard1Data->guard1->GetPosition().y);
	if (deltaX <= 40)
		return true;
	return false;
}

Guard1BeatState::StateName Guard1BeatState::GetState()
{
	return Guard1State::Beat;
}

