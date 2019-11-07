#include "JafarSnakeState.h"

JafarSnakeState::JafarSnakeState(JafarData * jafarData)
{
	this->mJafarData = jafarData;
}

JafarSnakeState::~JafarSnakeState()
{
}

void JafarSnakeState::Update(float dt)
{
	if (this->mJafarData->jafar->GetCurrentAnimation()->mCurrentIndex == this->mJafarData->jafar->GetCurrentAnimation()->mTotalFrame&&isThrow == true)
	{
		isThrow = false;
		Entity* tmp = nullptr;

			if (mJafarData->jafar->getFaceDirection() == Entity::FaceDirection::LEFT)
				tmp = new JafarWeapon2(D3DXVECTOR2(this->mJafarData->jafar->GetBound().left + 20, this->mJafarData->jafar->GetBound().bottom), this->mJafarData->jafar->mPlayer);
			else
				tmp = new JafarWeapon2(D3DXVECTOR2(this->mJafarData->jafar->GetBound().right - 20, this->mJafarData->jafar->GetBound().bottom), this->mJafarData->jafar->mPlayer);
		mJafarData->jafar->mPlayer->getGameMap()->InsertWeapon(tmp);
		Sound::getInstance()->play("JafarSnake", false, 1);
	}
	if (this->mJafarData->jafar->GetCurrentAnimation()->mCurrentIndex == 1)
		isThrow = true;
}

void JafarSnakeState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::AppleAladdin:
		mJafarData->jafar->TakeDamage(1);
		mJafarData->jafar->SetTimeImmortal(1);
		break;
	}

}

JafarState::StateName JafarSnakeState::GetState()
{
	return JafarState::Snake;
}
