#include "Guard3.h"
#include "Guard3StandState.h"
Guard3::Guard3()
{

	this->Tag = Entity::Guard3;
	this->mGuard3Data = new Guard3Data();
	this->mGuard3Data->guard3 = this;
	this->vx = 0;
	this->vy = 0;
	mCurrentAnimation = new Animation();
	int random = rand() % 2;
	if (random == 1)
	{
		this->SetState(new Guard3StandState(this->mGuard3Data));
	}
	else
	{
		this->SetState(new Guard3DanceState(this->mGuard3Data));
	}

	x = this->mGuard3Data->guard3->GetPosition().x;
	faceDirection = Entity::FaceDirection::LEFT;
	// khoang gioi han di chuyen cua enemy
	minX = x - 100;
	maxX = x + 100;
}

Guard3::Guard3(D3DXVECTOR2 position, Player *player)
{
	this->Tag = Entity::Guard3;
	this->HP = 1;
	this->mGuard3Data = new Guard3Data();
	this->mGuard3Data->guard3 = this;
	this->mPlayer = player;
	this->vx = 0;
	this->vy = 0;
	mCurrentAnimation = new Animation();
	this->SetState(new Guard3StandState(this->mGuard3Data));
	this->SetPosition(position);
	this->SetReverse(false);
	x = this->mGuard3Data->guard3->GetPosition().x;

	// khoang gioi han di chuyen cua enemy
	minX = x - 50;
	maxX = x + 50;
}

Guard3::~Guard3()
{

}

void Guard3::Update(float dt)
{
	if (this->mCurrentAnimation->mCurrentIndex == this->mCurrentAnimation->mTotalFrame&&isDestroy == true)
	{
		isDeleted = true;
		return;
	}
	if (this->mGuard3Data->guard3->mPlayer->GetPosition().x - this->mGuard3Data->guard3->GetPosition().x > 0)
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

	if (this->mGuard3Data->state)
	{
		this->mGuard3Data->state->Update(dt);
	}
	if (this->GetPosition().x + mGuard3Data->guard3->GetVx()*dt<mGuard3Data->guard3->minX
		|| this->GetPosition().x + mGuard3Data->guard3->GetVx()*dt>mGuard3Data->guard3->maxX)
	{
		this->mGuard3Data->guard3->SetState(new Guard3StandState(mGuard3Data));
		return;
	}
	else
	Entity::Update(dt);

}

bool Guard3::IsNearToPlayer()
{
	int deltaX = this->mPlayer->GetPosition().x - this->mGuard3Data->guard3->GetPosition().x;
	int deltaY = this->mPlayer->GetPosition().y - this->mGuard3Data->guard3->GetPosition().y;
	if (abs(deltaX) <= 250 && abs(deltaY) <= 30)
	{
		return true;
	}
	return false;
}

bool Guard3::IsInAttackRange()
{
	int deltaX = abs(this->mGuard3Data->guard3->mPlayer->GetPosition().x - this->mGuard3Data->guard3->GetPosition().x);
	int deltaY = abs(this->mGuard3Data->guard3->mPlayer->GetPosition().y - this->mGuard3Data->guard3->GetPosition().y);
	if (deltaX <= 200&&deltaY<50)
		return true;
	return false;
}

bool Guard3::IsInActiveRegion()
{

	if ((mGuard3Data->guard3->GetPosition().x >= minX) && (mGuard3Data->guard3->GetPosition().x <= maxX))
	{
		return true;
	}
	else
	{
		return false;
	}

}


void Guard3::SetState(Guard3State * newState)
{
	delete this->mGuard3Data->state;
	this->mGuard3Data->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();
}

Guard3State::StateName Guard3::GetState()
{
	return mCurrentState;
}

void Guard3::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}
void Guard3::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(), transform);
}

RECT Guard3::GetBound()
{
	
	POINT tmp = this->mGuard3Data->guard3->GetCurrentAnimation()->GetAnchorPoint();
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

void Guard3::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (this->mGuard3Data->state)
		this->mGuard3Data->state->OnCollision(impactor, data, side);

	if (this->HP <= 0)
	{
		if (isDestroy == false)
		{
			this->isDestroy = true;
			delete mCurrentAnimation;
			mCurrentAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.25f, NULL);
			Sound::getInstance()->play("BalloonPop", false, 1);
		}
	}
}

Animation *Guard3::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

Animation * Guard3::GetAnimation(Guard3State::StateName state)
{
	switch (state)
	{
	case Guard3State::Run:
		return mAnimationRun;
		break;
	case Guard3State::Dance:
		return mAnimationDance;
		break;
	case Guard3State::Beaten:
		return mAnimationBeaten;
		break;
	case Guard3State::Stand:
		return mAnimationStand;
		break;
	case Guard3State::Throw:
		return mAnimationThrow;
		break;
	}
}


void Guard3::SetReverse(bool flag)
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

bool Guard3::GetReverse()
{
	return mCurrentReverse;
}

void Guard3::changeAnimation(Guard3State::StateName state)
{
	switch (state)
	{
	case Guard3State::Run:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard3rdRun", 8, 0.2f, NULL);
		break;
	case Guard3State::Dance:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard3rdDance", 7, 0.15f, NULL);
		break;
	case Guard3State::Throw:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard3rdThrow", 5, 0.25f, NULL);
		break;
	case Guard3State::Stand:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard3rdStand", 1, 0.15f, NULL);
		break;
	case Guard3State::Beaten:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::GUARDS, "Guard3rdBeaten", 7, 0.3f, NULL);
		break;
	}
}
void Guard3::SetGameMap(GameMap *gamemap)
{
	this->mGameMap = gamemap;
}

GameMap* Guard3::getGameMap()
{
	return this->mGameMap;
}

void Guard3::LimitDistance()
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