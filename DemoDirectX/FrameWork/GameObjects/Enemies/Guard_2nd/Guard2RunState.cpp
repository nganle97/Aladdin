#include "Guard2RunState.h"

Guard2RunState::Guard2RunState(Guard2Data * guard2Data)
{
	this->mGuard2Data = guard2Data;
	mGuard2Data->guard2->SetVy(0);
	
	if (this->mGuard2Data->guard2->getFaceDirection() == Entity::LEFT)
	{
		mGuard2Data->guard2->SetVx(-mGuard2Data->guard2->Vx);
		this->mGuard2Data->guard2->SetReverse(false);
	}
	else 
	{
		mGuard2Data->guard2->SetVx(mGuard2Data->guard2->Vx);
		this->mGuard2Data->guard2->SetReverse(true);
	}
}

Guard2RunState::~Guard2RunState()
{
}

void Guard2RunState::Update(float dt)
{
	if (this->mGuard2Data->guard2->IsNearToPlayer() == true)
	{
		if (this->mGuard2Data->guard2->getFaceDirection() == Entity::FaceDirection::LEFT)
			this->mGuard2Data->guard2->SetVx(-mGuard2Data->guard2->Vx);
		else
			this->mGuard2Data->guard2->SetVx(mGuard2Data->guard2->Vx);
	}
	else
	{
		this->mGuard2Data->guard2->SetState(new Guard2ArouseState(mGuard2Data));
		return;
	}
	if (this->mGuard2Data->guard2->IsInAttackRange() == true && this->mGuard2Data->guard2->GetState() != Guard1State::Beaten)
		this->mGuard2Data->guard2->SetState(new Guard2DartState(mGuard2Data));
}

void Guard2RunState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
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


Guard2State::StateName Guard2RunState::GetState()
{
	return Guard2State::Run;
}
