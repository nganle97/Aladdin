#include "Jafar.h"

Jafar::Jafar()
{

	this->Tag = Entity::Jafar;
	this->mJafarData = new JafarData();
	this->mJafarData->jafar = this;
	this->vx = 0;
	this->vy = 0;
	mCurrentAnimation = new Animation();
	this->SetState(new JafarOriginalState(this->mJafarData));
	faceDirection = Entity::FaceDirection::RIGHT;
	
}

Jafar::Jafar(D3DXVECTOR2 position, Player *player)
{
	this->Tag = Entity::Jafar;
	this->HP = 10;
	this->mJafarData = new JafarData();
	this->mJafarData->jafar = this;
	this->mPlayer = player;
	this->vx = 0;
	this->vy = 0;
	mCurrentAnimation = new Animation();
	this->SetPosition(position);
	faceDirection = Entity::FaceDirection::LEFT;
	this->SetState(new JafarOriginalState(this->mJafarData));



}

Jafar::~Jafar()
{

}

void Jafar::Update(float dt)
{ 
	if (IsInActiveRegion() == false) return;
	if (this->mCurrentAnimation->mCurrentIndex == this->mCurrentAnimation->mTotalFrame&&isDestroy == true)
	{
		isDeleted = true;
		return;
	}
	if (this->mJafarData->jafar->mPlayer->GetPosition().x > this->mJafarData->jafar->GetPosition().x )
	{
		this->faceDirection = Entity::FaceDirection::RIGHT;
		this->SetReverse(false);
	}
	else
	{
		this->faceDirection = Entity::FaceDirection::LEFT;
		this->SetReverse(true);
	}

	mCurrentAnimation->Update(dt);

	if (this->mJafarData->state)
	{
		this->mJafarData->state->Update(dt);
	}

	Entity::Update(dt);

}

bool Jafar::IsInActiveRegion()
{
	if (abs(mPlayer->GetPosition().x - this->GetPosition().x) < 400 && abs(mPlayer->GetPosition().y - this->GetPosition().y) < 200)
		return true;
	return false;
}

void Jafar::SetState(JafarState * newState)
{
	delete this->mJafarData->state;
	this->mJafarData->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();
}

JafarState::StateName Jafar::GetState()
{
	return mCurrentState;
}

void Jafar::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}
void Jafar::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(), transform);
}

RECT Jafar::GetBound()
{
	POINT tmp = this->mJafarData->jafar->GetCurrentAnimation()->GetAnchorPoint();
	RECT rect;
	if (tmp.x == -1 && tmp.y == -1)
	{
		rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 2;
		rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
		rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight();
		rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight();
	}
	else
	{
		if (this->mCurrentReverse == false)
		{
			rect.left = this->posX - tmp.x;
			rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
		}
		else
		{
			rect.right = this->posX + tmp.x;
			rect.left = rect.right - mCurrentAnimation->GetSprite()->GetWidth();
		}
		rect.top = this->posY - tmp.y;
		rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight();
	}
	return rect;
}

void Jafar::OnCollision(Entity * impactor,   Entity::CollisionReturn data,Entity::SideCollisions side)
{
	if (this->mJafarData->jafar->GetTimeImmortal() > 0)
		return;
	if (this->mJafarData->state)
		this->mJafarData->state->OnCollision(impactor, side, data);
	if (this->HP <= 0&&this->GetState()==JafarState::Snake)
	{
		if (isDestroy == false)
		{
			this->isDestroy = true;
			delete mCurrentAnimation;
			mCurrentAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.25f, NULL);
		}
		
	}
	else 
		if (this->HP <= 0 && this->GetState() == JafarState::Original)
		{
			this->HP = 10;
			this->SetTimeImmortal(1);
			this->SetState(new JafarSnakeState(mJafarData));
		}

}

Animation *Jafar::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

Animation * Jafar::GetAnimation(JafarState::StateName state)
{
	switch (state)
	{
	case JafarState::Original:
		return mAnimationOriginal;
		break;
	case JafarState::Snake:
		return mAnimationSnake;
		break;
	}
}


void Jafar::SetReverse(bool flag)
{
	mCurrentReverse = flag;
	// Thay đổi faceDirection;
	if (flag == false)
	{
		faceDirection = Entity::FaceDirection::LEFT;
	}
	else
	{
		faceDirection = Entity::FaceDirection::RIGHT;
	}

}

bool Jafar::GetReverse()
{
	return mCurrentReverse;
}

void Jafar::changeAnimation(JafarState::StateName state)
{
	switch (state)
	{
	case JafarState::Original:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::JAFAR, "Jafar", 8, 0.2f, NULL);//0.2
		break;
	case JafarState::Snake:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::JAFAR, "Snake", 11, 0.2f, NULL);//0.2
		break;
	}
}
