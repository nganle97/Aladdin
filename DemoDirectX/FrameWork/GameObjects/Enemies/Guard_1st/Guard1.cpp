#include "Guard1.h"
#include "Guard1StandState.h"
Guard1::Guard1()
{

	this->Tag = Entity::Guard1;
	this->mGuard1Data = new Guard1Data();
	this->mGuard1Data->guard1 = this;
	this->vx = 0;
	this->vy = 0;
	mCurrentAnimation = new Animation();
	this->SetState(new Guard1RunState(this->mGuard1Data));
	mCurrentAnimation->SetLoop(true, 3, 3);

	x = this->mGuard1Data->guard1->GetPosition().x;
	faceDirection = Entity::FaceDirection::LEFT;
	// khoang gioi han di chuyen cua enemy
	minX = x - 100;
	maxX = x + 100;
}
Guard1::Guard1(D3DXVECTOR2 position,Player* mplayer)
{
	this->Tag = Entity::Guard1;
	this->HP = 2;
	this->mGuard1Data = new Guard1Data();
	this->mGuard1Data->guard1 = this;
	this->mPlayer = mplayer;
	if (mplayer->GetPosition().x - position.x > 0)
		faceDirection = Entity::FaceDirection::RIGHT;
	else faceDirection = Entity::FaceDirection::LEFT;
	this->vx = 0;
	this->vy = 0;
	mCurrentAnimation = new Animation();
	this->SetState(new Guard1RunState(this->mGuard1Data));
	this->SetPosition(position);
	x = this->mGuard1Data->guard1->GetPosition().x;

	this->Vx = 20.0f;
	// khoang gioi han di chuyen cua enemy
	minX = x - 100;
	maxX = x + 100;
}

Guard1::~Guard1()
{

}

void Guard1::Update(float dt)
{
	if (this->mCurrentAnimation->mCurrentIndex == this->mCurrentAnimation->mTotalFrame&&isDestroy == true)
	{
		isDeleted = true;
		return;
	}

	if (this->mGuard1Data->guard1->mPlayer->GetPosition().x - this->mGuard1Data->guard1->GetPosition().x > 0)
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

	if (this->mGuard1Data->state)
	{
		this->mGuard1Data->state->Update(dt);
	}
	if (this->GetPosition().x + mGuard1Data->guard1->GetVx()*dt<mGuard1Data->guard1->minX
		|| this->GetPosition().x + mGuard1Data->guard1->GetVx()*dt>mGuard1Data->guard1->maxX)
	{
		this->mGuard1Data->guard1->SetState(new Guard1StandState(mGuard1Data));
		return;
	}
	else
		Entity::Update(dt);
}

bool Guard1::IsNearToPlayer()
{
	if (this->mPlayer->GetPosition().x<minX-40|| this->mPlayer->GetPosition().x>maxX+40) return false;
	int deltaX = this->mPlayer->GetPosition().x - this->mGuard1Data->guard1->GetPosition().x;
	int deltaY = this->mPlayer->GetPosition().y - this->mGuard1Data->guard1->GetPosition().y;
	if (abs(deltaX) <= 200 && abs(deltaY) <= 50)
	{
		return true;
	}
	return false;

}

bool Guard1::IsInAttackRange()
{
	int deltaX = abs(this->mGuard1Data->guard1->mPlayer->GetPosition().x - this->mGuard1Data->guard1->GetPosition().x);
	int deltaY = abs(this->mGuard1Data->guard1->mPlayer->GetPosition().y - this->mGuard1Data->guard1->GetPosition().y);
	if (deltaX <= 110)
		return true;
	return false;
}

bool Guard1::IsInActiveRegion()
{

	if ((mGuard1Data->guard1->GetPosition().x >= minX) && (mGuard1Data->guard1->GetPosition().x <= maxX))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


void Guard1::SetState(Guard1State * newState)
{
	delete this->mGuard1Data->state;
	this->mGuard1Data->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();
}

Guard1State::StateName Guard1::GetState()
{
	return mCurrentState;
}

void Guard1::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Guard1::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(), transform);
}

RECT Guard1::GetBound()
{
	
	POINT tmp = this->mGuard1Data->guard1->GetCurrentAnimation()->GetAnchorPoint();
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

RECT Guard1::GetBoundBody()
{
	RECT rect;
	rect.left = this->posX - 17;
	rect.right = this->posX + 17;
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight();
	rect.bottom = this->posY;
	return rect;
}

RECT Guard1::GetBoundWeapon()
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

void Guard1::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (this->mGuard1Data->state)
	this->mGuard1Data->state->OnCollision(impactor, data, side);
	if (this->HP <= 0)
	{
		this->isDestroy = true;
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.15f, NULL);
		Sound::getInstance()->play("BalloonPop", false, 1);
	}
	
}


Animation *Guard1::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

Animation * Guard1::GetAnimation(Guard1State::StateName state)
{
	switch (state)
	{
	case Guard1State::Run :
		return mAnimationRun;
		break;
	case Guard1State::Beat:
		return mAnimationBeat;
		break;
	case Guard1State::Beaten:
		return mAnimationBeaten;
		break;
	}
}


void Guard1::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

bool Guard1::GetReverse()
{
	return mCurrentReverse;
}

void Guard1::changeAnimation(Guard1State::StateName state)
{
	switch (state)
	{
	case Guard1State::Run:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard1stRun", 8, 0.2f, NULL);
		break;
	case Guard1State::Beat:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard1stBeat", 6, 0.15f, NULL);
		break;
	case Guard1State::Beaten:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard1stBeaten", 9, 0.15f, NULL);
		break;
	case Guard1State::Stand:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard1stBeaten", 1, 0.15f, NULL);
		break;
	}
}
void Guard1::OnSetPosition(D3DXVECTOR3 pos)
{
	mCurrentAnimation->SetPosition(pos);
}