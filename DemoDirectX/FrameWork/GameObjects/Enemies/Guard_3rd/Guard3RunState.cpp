#include "Guard3RunState.h"

Guard3RunState::Guard3RunState(Guard3Data * guard3Data)
{
	{
		this->mGuard3Data = guard3Data;
		this->Vx = 20.0f;
		mGuard3Data->guard3->SetVy(0);

		if (this->mGuard3Data->guard3->getFaceDirection() == Entity::LEFT)
		{
			mGuard3Data->guard3->SetVx(-Vx);
			this->mGuard3Data->guard3->SetReverse(false);
		}
		else
		{
			mGuard3Data->guard3->SetVx(Vx);
			this->mGuard3Data->guard3->SetReverse(true);
		}
	}
}

Guard3RunState::~Guard3RunState()
{

}

void Guard3RunState::Update(float dt)
{
	//đổi hướng di chuyển của Guard3 khi Aladdin sang hướng khác so với guard 3.
	if (mGuard3Data->guard3->mPlayer->GetPosition().x - mGuard3Data->guard3->GetPosition().x > 0)
	{
		this->mGuard3Data->guard3->SetVx(Vx);
	}
	else
	{
		this->mGuard3Data->guard3->SetVx(-Vx);
	}
	if (mGuard3Data->guard3->IsInAttackRange() == true)
	{
		this->mGuard3Data->guard3->SetState(new Guard3StandState(mGuard3Data));
		return;
	}
}

void Guard3RunState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		if (this->mGuard3Data->guard3->GetTimeImmortal() <= 0)
		{
			mGuard3Data->guard3->SetState(new Guard3BeatenState(mGuard3Data));
			Sound::getInstance()->play("GuardPants", false, 1);
		}
		break;
	case Entity::EntityTypes::Aladdin:
		if (this->mGuard3Data->guard3->mPlayer->IsMakeDamage() == true && this->mGuard3Data->guard3->GetTimeImmortal() <= 0)
		{
			if (GameCollision::isCollide(impactor->GetBoundWeapon(), mGuard3Data->guard3->GetBound()) == true)
			{
				mGuard3Data->guard3->TakeDamage(1);
				mGuard3Data->guard3->SetTimeImmortal(0.5);
				mGuard3Data->guard3->SetState(new Guard3BeatenState(mGuard3Data));
				Sound::getInstance()->play("GuardPants", false, 1);
			}
		}
		break;
	}
}
Guard3State::StateName Guard3RunState::GetState()
{
	return Guard3State::Run;
}
