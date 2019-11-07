#include "Guard2ArouseState.h"

Guard2ArouseState::Guard2ArouseState(Guard2Data * guard2Data)
{
	this->mGuard2Data = guard2Data;
	mGuard2Data->guard2->SetVy(0);
	mGuard2Data->guard2->SetVx(0);
	
}

Guard2ArouseState::~Guard2ArouseState()
{

}

void Guard2ArouseState::Update(float dt)
{
	if (this->mGuard2Data->guard2->IsInAttackRange() == true)
	{
		if (this->GetState() != Guard2State::Dart&&this->GetState() != Guard2State::Cut)
		{
			int tmp = rand() % 2;
			
			if (tmp==0)
				this->mGuard2Data->guard2->SetState(new Guard2DartState(mGuard2Data));
			else
				this->mGuard2Data->guard2->SetState(new Guard2CutState(mGuard2Data));
			return;
		}
	}
	else
		if (this->mGuard2Data->guard2->IsNearToPlayer() == true&&this->GetState()!=Guard2State::Run)
		{
			if ((mGuard2Data->guard2->GetPosition().x + (-mGuard2Data->guard2->Vx*dt) < mGuard2Data->guard2->minX&&this->mGuard2Data->guard2->getFaceDirection() == Entity::LEFT)
				|| (mGuard2Data->guard2->GetPosition().x + mGuard2Data->guard2->GetVx()*dt > mGuard2Data->guard2->maxX&&this->mGuard2Data->guard2->getFaceDirection() == Entity::RIGHT))
			{
				return;
			}
			else
			{
				this->mGuard2Data->guard2->SetState(new Guard2RunState(mGuard2Data));
				return;
			}
		}

}

void Guard2ArouseState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
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

Guard2State::StateName Guard2ArouseState::GetState()
{
	return Guard2State::Arouse;
}
