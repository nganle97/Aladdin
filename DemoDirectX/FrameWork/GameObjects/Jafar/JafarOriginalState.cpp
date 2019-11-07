#include "JafarOriginalState.h"

JafarOriginalState::JafarOriginalState(JafarData * jafarData)
{
	this->mJafarData = jafarData;
}

JafarOriginalState::~JafarOriginalState()
{
}

void JafarOriginalState::Update(float dt)
{

	if (timeThrow<=0)
	{

		Entity* tmp = nullptr;
		{
			timeThrow = 0.25;
			if (mJafarData->jafar->getFaceDirection() == Entity::FaceDirection::LEFT)
				tmp = new JafarWeapon(D3DXVECTOR2(this->mJafarData->jafar->GetBound().left + 20, this->mJafarData->jafar->GetBound().top + 20), this->mJafarData->jafar->mPlayer);
			else
				tmp = new JafarWeapon(D3DXVECTOR2(this->mJafarData->jafar->GetBound().right - 20, this->mJafarData->jafar->GetBound().top + 20), this->mJafarData->jafar->mPlayer);
		}
		mJafarData->jafar->mPlayer->getGameMap()->InsertWeapon(tmp);
	}
	else (timeThrow -= dt);
}

void JafarOriginalState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

	switch (impactor->Tag)
	{
	case Entity::Aladdin:
		if (this->mJafarData->jafar->mPlayer->IsMakeDamage()==true&&this->mJafarData->jafar->GetTimeImmortal()<=0)

			this->mJafarData->jafar-> TakeDamage(1);
		this->mJafarData->jafar->SetTimeImmortal(1);
		if (this->mJafarData->jafar->mPlayer->GetTimeImmortal() <= 0)
		{
			this->mJafarData->jafar->mPlayer->TakeDamage(1);
			this->mJafarData->jafar->mPlayer->SetTimeImmortal(1);
		}
		break;
	case Entity::AppleAladdin:
		if (impactor->IsDestroy() == false)
		{
			this->mJafarData->jafar->TakeDamage(1);
			this->mJafarData->jafar->SetTimeImmortal(1);
		}
		break;
	}
}

JafarState::StateName JafarOriginalState::GetState()
{
	return JafarState::Original;
}
