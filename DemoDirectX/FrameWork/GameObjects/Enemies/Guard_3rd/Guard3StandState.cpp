#include "Guard3StandState.h"

Guard3StandState::Guard3StandState(Guard3Data * guard3Data)
{
	this->mGuard3Data = guard3Data;
	mGuard3Data->guard3->SetVy(0);
	mGuard3Data->guard3->SetVx(0);
	if (this->mGuard3Data->guard3->getFaceDirection() == Entity::FaceDirection::LEFT)
	{
		this->mGuard3Data->guard3->SetReverse(false);
	}
	else this->mGuard3Data->guard3->SetReverse(true);
}

Guard3StandState::~Guard3StandState()
{
}

void Guard3StandState::Update(float dt)
{
	if (this->mGuard3Data->guard3->IsInAttackRange() == true)
	{
		if (this->GetState() != Guard3State::Throw)
		{
			this->mGuard3Data->guard3->SetState(new Guard3ThrowState(mGuard3Data));
			return;
		}
	}
	else if (this->mGuard3Data->guard3->IsNearToPlayer() == true)
	{
		if (this->GetState() != Guard3State::Throw)
		{
			this->mGuard3Data->guard3->SetState(new Guard3RunState(mGuard3Data));
			return;
		}
	}

}

void Guard3StandState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mGuard3Data->guard3->GetTimeImmortal() <= 0)
		{
			mGuard3Data->guard3->SetState(new Guard3BeatenState(mGuard3Data));
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
			}
		}
		break;
	}
}

Guard3State::StateName Guard3StandState::GetState()
{
	return Guard3State::Stand;
}
