#include "Guard1StandState.h"

Guard1StandState::Guard1StandState(Guard1Data * Guard1Data)
{
	this->mGuard1Data = Guard1Data;
	mGuard1Data->guard1->SetVy(0);
	mGuard1Data->guard1->SetVx(0);
	if (this->mGuard1Data->guard1->getFaceDirection() == Entity::FaceDirection::LEFT)
	{
		this->mGuard1Data->guard1->SetReverse(false);
	}
	else this->mGuard1Data->guard1->SetReverse(true);
}

Guard1StandState::~Guard1StandState()
{
}

void Guard1StandState::Update(float dt)
{
	if (this->mGuard1Data->guard1->IsInAttackRange() == true)
	{
		if (this->GetState() != Guard1State::Beat)
		{
			this->mGuard1Data->guard1->SetState(new Guard1BeatState(mGuard1Data));
			return;
		}
	}
	else if (this->mGuard1Data->guard1->IsNearToPlayer() == true)
	{
		if (this->GetState() != Guard1State::Run)
		{
			this->mGuard1Data->guard1->SetState(new Guard1RunState(mGuard1Data));
			return;
		}
	}

}

void Guard1StandState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
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
		if (this->mGuard1Data->guard1->mPlayer->IsMakeDamage() == true && this->mGuard1Data->guard1->GetTimeImmortal() <= 0)
		{
			if (GameCollision::isCollide(mGuard1Data->guard1->mPlayer->GetBoundWeapon(), mGuard1Data->guard1->GetBoundBody()) == true)
			{
				mGuard1Data->guard1->TakeDamage(1);
				mGuard1Data->guard1->SetTimeImmortal(1);
				mGuard1Data->guard1->SetState(new Guard1BeatenState(mGuard1Data));
				Sound::getInstance()->play("GuardHit1", false, 1);
			}
		}
		break;
	}
}

Guard1State::StateName Guard1StandState::GetState()
{
	return Guard1State::Stand;
}
