#include "Guard2.h"

Guard2::Guard2()
{

	this->Tag = Entity::Guard2;
	this->mGuard2Data = new Guard2Data();
	this->mGuard2Data->guard2 = this;
	this->vx = 0;
	this->vy = 0;
	mCurrentAnimation = new Animation();
	this->SetState(new Guard2ArouseState(this->mGuard2Data));


	x = this->mGuard2Data->guard2->GetPosition().x;

	// khoang gioi han di chuyen cua enemy
	minX = x - 80;
	maxX = x + 80;
}

Guard2::Guard2(D3DXVECTOR2 position,Player* mplayer)
{
	this->Tag = Entity::Guard2;
	this->HP = 2;
	this->Vx = 30.0f;
	this->mGuard2Data = new Guard2Data();
	this->mGuard2Data->guard2 = this;
	this->mPlayer = mplayer;
	this->vx = 0;
	this->vy = 0;
	if (mplayer->GetPosition().x - position.x > 0)
		faceDirection = Entity::FaceDirection::RIGHT;
	else faceDirection = Entity::FaceDirection::LEFT;
	mCurrentAnimation = new Animation();
	this->SetState(new Guard2ArouseState(this->mGuard2Data));
	this->SetPosition(position);
	x = this->mGuard2Data->guard2->GetPosition().x;

	// khoang gioi han di chuyen cua enemy
	minX = x - 100;
	maxX = x + 100;
}

Guard2::~Guard2()
{

}

void Guard2::Update(float dt)
{
	if (this->mCurrentAnimation->mCurrentIndex == this->mCurrentAnimation->mTotalFrame&&isDestroy == true)
	{
		isDeleted = true;
		return;
	}
	
	if (this->mGuard2Data->guard2->mPlayer->GetPosition().x - this->mGuard2Data->guard2->GetPosition().x > 0)
	{
		this->faceDirection = Entity::FaceDirection::RIGHT;
		this->SetReverse(true);
	}
	else
	{
		this->faceDirection = Entity::FaceDirection::LEFT;
		this->SetReverse(false);
	}
	mCurrentAnimation->Update(dt);

	if (this->mGuard2Data->state)
	{
		this->mGuard2Data->state->Update(dt);
	}
	if (this->GetPosition().x + mGuard2Data->guard2->GetVx()*dt<mGuard2Data->guard2->minX
		|| this->GetPosition().x + mGuard2Data->guard2->GetVx()*dt>mGuard2Data->guard2->maxX)
	{
		if (this->GetState()!=Guard2State::Arouse)
		this->mGuard2Data->guard2->SetState(new Guard2ArouseState(mGuard2Data));
		return;
	}
	else
		Entity::Update(dt);

}

bool Guard2::IsNearToPlayer()
{
	int deltaX = this->mPlayer->GetPosition().x - this->mGuard2Data->guard2->GetPosition().x;
	int deltaY = this->mPlayer->GetPosition().y - this->mGuard2Data->guard2->GetPosition().y;
	if (abs(deltaX) <= 200 && abs(deltaY) <= 50)
	{
		return true;
	}
	return false;

}

bool Guard2::IsInActiveRegion()
{

	if ((mGuard2Data->guard2->GetPosition().x >= minX) && (mGuard2Data->guard2->GetPosition().x <= maxX))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Guard2::IsInAttackRange()
{
	int deltaX = abs(this->mGuard2Data->guard2->mPlayer->GetPosition().x - this->mGuard2Data->guard2->GetPosition().x);
	int deltaY = abs(this->mGuard2Data->guard2->mPlayer->GetPosition().y - this->mGuard2Data->guard2->GetPosition().y);
	if (deltaX <= 110&&deltaY<=50)
		return true;
	return false;
}

void Guard2::SetState(Guard2State * newState)
{
	delete this->mGuard2Data->state;
	this->mGuard2Data->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();
}

Guard2State::StateName Guard2::GetState()
{
	return mCurrentState;
}

void Guard2::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Guard2::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(), transform);
}

RECT Guard2::GetBound()
{
	POINT tmp = this->mGuard2Data->guard2->GetCurrentAnimation()->GetAnchorPoint();
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

RECT Guard2::GetBoundBody()
{
	RECT rect;
	rect.left = this->posX - 20;
	rect.right = this->posX + 20;
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight();
	rect.bottom = this->posY;
	return rect;
}

RECT Guard2::GetBoundWeapon()
{
	RECT rect = this->GetBound();;
	if (faceDirection == FaceDirection::RIGHT)
	{
		rect.left += this->mCurrentAnimation->GetSprite()->GetWidth() / 2;
	}
	else
	{
		rect.right -= this->mCurrentAnimation->GetSprite()->GetWidth() / 2;
	}
	return rect;
}

void Guard2::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

	if (this->mGuard2Data->state)
		this->mGuard2Data->state->OnCollision(impactor, data, side);
	
	if (this->HP <= 0)
	{
		//this->isDeleted = true;
		if (isDestroy == false)
		{
			this->isDestroy = true;
			delete mCurrentAnimation;
			mCurrentAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.15f, NULL);
			Sound::getInstance()->play("BalloonPop", false, 1);
		}
	}
	

}

Animation *Guard2::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

Animation * Guard2::GetAnimation(Guard2State::StateName state)
{
	switch (state)
	{
	case Guard2State::Arouse:
		return mAnimationArouse;
		break;
	case Guard2State::Run:
		return mAnimationRun;
		break;
	case Guard2State::Cut:
		return mAnimationCut;
		break;
	case Guard2State::Dart:
		return mAnimationDart;
	case Guard2State::Burned:
		return mAnimationBurned;
		break;
		break;
	case Guard2State::Beaten:
		return mAnimationBeaten;
		break;
	}
}


void Guard2::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

bool Guard2::GetReverse()
{
	return mCurrentReverse;
}

void Guard2::changeAnimation(Guard2State::StateName state)
{
	switch (state)
	{
	case Guard2State::Arouse:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard2ndArouse", 6, 0.4f, NULL);//0.4f
		break;
	case Guard2State::Dart:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard2ndDart", 6, 0.15f, NULL);//0.15f
		break;
	case Guard2State::Burned:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard2ndBurned", 6, 0.15f, NULL);//0.15f
		break;
	case Guard2State::Cut:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard2ndCut", 5, 0.15f, NULL);//0.15f
		break;
	case Guard2State::Run:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard2ndRun", 8, 0.15f, NULL);//0.15f
		break;
	case Guard2State::Beaten:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard2ndBeaten", 6, 0.15f, NULL);//0.15f
		break;
	}
}
void Guard2::OnSetPosition(D3DXVECTOR3 pos)
{
	mCurrentAnimation->SetPosition(pos);
}
void Guard2::LimitDistance()
{
	if (this->GetPosition().x < minX)
	{
		this->SetPosition(minX, this->GetPosition().y);
	}
	else
		if (this->GetPosition().x > maxX)
		{
			this->SetPosition(maxX, this->GetPosition().y);
		}
}