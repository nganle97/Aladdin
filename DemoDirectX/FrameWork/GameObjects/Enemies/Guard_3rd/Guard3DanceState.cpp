#include "Guard3DanceState.h"

Guard3DanceState::Guard3DanceState(Guard3Data * guard3Data)
{
	this->mGuard3Data = guard3Data;
	mGuard3Data->guard3->SetVy(0);
	mGuard3Data->guard3->SetVx(0);
}

Guard3DanceState::~Guard3DanceState()
{
}

void Guard3DanceState::Update(float dt)
{
	
}
void Guard3DanceState::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
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
			mGuard3Data->guard3->TakeDamage(1);
			mGuard3Data->guard3->SetTimeImmortal(0.5);
			mGuard3Data->guard3->SetState(new Guard3BeatenState(mGuard3Data));
		}
		break;
	}
}

Guard3State::StateName Guard3DanceState::GetState()
{
	return Guard3State::Dance;
}
