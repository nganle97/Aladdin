#include "Guard1RunState.h"
#include "Guard1StandState.h"

Guard1RunState::Guard1RunState(Guard1Data * guard1Data)
{
	this->mGuard1Data = guard1Data;
	if (this->mGuard1Data->guard1->getFaceDirection() == Entity::FaceDirection::LEFT)
	{
		this->mGuard1Data->guard1->SetReverse(false);
		this->mGuard1Data->guard1->SetVx(-this->mGuard1Data->guard1->Vx);
	}
	else
	{
		this->mGuard1Data->guard1->SetVx(this->mGuard1Data->guard1->Vx);
		this->mGuard1Data->guard1->SetReverse(true);
	}
	
}

Guard1RunState::~Guard1RunState()
{
}

void Guard1RunState::Update(float dt)
{
	if (this->mGuard1Data->guard1->IsNearToPlayer() == true)
	{
		if (this->mGuard1Data->guard1->getFaceDirection() == Entity::FaceDirection::LEFT)
			this->mGuard1Data->guard1->SetVx(-mGuard1Data->guard1->Vx);
		else
			this->mGuard1Data->guard1->SetVx(mGuard1Data->guard1->Vx);
	}
	else
	{
		this->mGuard1Data->guard1->SetState(new Guard1StandState(mGuard1Data));
		return;
	}
	if (this->mGuard1Data->guard1->IsInAttackRange() == true && this->mGuard1Data->guard1->GetState() != Guard1State::Beaten)
		this->mGuard1Data->guard1->SetState(new Guard1BeatState(mGuard1Data));
}


void Guard1RunState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mGuard1Data->guard1->GetTimeImmortal() <= 0)
		{
			mGuard1Data->guard1->TakeDamage(1);
			mGuard1Data->guard1->SetTimeImmortal(1);
			mGuard1Data->guard1->SetState(new Guard1BeatenState(mGuard1Data));
			Sound::getInstance()->play("GuardHit1", false, 1);
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

Guard1State::StateName Guard1RunState::GetState()
{
	return Guard1State::Run;
}

