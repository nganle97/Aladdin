#include "CivilianEnemy4th.h"

CivilianEnemy4th::CivilianEnemy4th()
{

	this->Tag = Entity::CivilianEnemy4th;
	this->mCivilianEnemy4thData = new CivilianEnemy4thData();
	this->mCivilianEnemy4thData->civilianEnemy4th = this;
	mCurrentAnimation = new Animation();
	this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thStandState(this->mCivilianEnemy4thData));
}

CivilianEnemy4th::CivilianEnemy4th(D3DXVECTOR2 position, Player* mplayer)
{
	this->Tag = Entity::CivilianEnemy4th;
	this->HP = 1;
	this->mCivilianEnemy4thData = new CivilianEnemy4thData();
	this->mCivilianEnemy4thData->civilianEnemy4th = this;
	if (mplayer->GetPosition().x - position.x > 0)
		faceDirection = Entity::FaceDirection::RIGHT;
	else faceDirection = Entity::FaceDirection::LEFT;
	mCurrentAnimation = new Animation();
	this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thStandState(this->mCivilianEnemy4thData));
	this->SetPosition(position);
	this->mPlayer = mplayer;
	int x = this->mCivilianEnemy4thData->civilianEnemy4th->GetPosition().x;

	this->Vx = 20.0f;
	// khoang gioi han di chuyen cua enemy
	minX = x - 100;
	maxX = x + 100;
}

CivilianEnemy4th::~CivilianEnemy4th()
{

}

void CivilianEnemy4th::Update(float dt)
{
	if (this->mCurrentAnimation->mCurrentIndex == this->mCurrentAnimation->mTotalFrame&&isDestroy == true)
	{
		isDeleted = true;
		return;
	}

	if (this->mCivilianEnemy4thData->civilianEnemy4th->mPlayer->GetPosition().x - this->mCivilianEnemy4thData->civilianEnemy4th->GetPosition().x > 0)
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

	if (this->mCivilianEnemy4thData->state)
	{
		this->mCivilianEnemy4thData->state->Update(dt);
	}
	if (this->GetPosition().x + mCivilianEnemy4thData->civilianEnemy4th->GetVx()*dt<mCivilianEnemy4thData->civilianEnemy4th->minX
		|| this->GetPosition().x + mCivilianEnemy4thData->civilianEnemy4th->GetVx()*dt>mCivilianEnemy4thData->civilianEnemy4th->maxX)
	{
		if (this->GetState()!=CivilianEnemy4thState::Stand)
		this->mCivilianEnemy4thData->civilianEnemy4th->SetState(new CivilianEnemy4thStandState(mCivilianEnemy4thData));
		return;
	}
	else
		Entity::Update(dt);

}

bool CivilianEnemy4th::IsNearToPlayer()
{
	int deltaX = this->mPlayer->GetPosition().x - this->mCivilianEnemy4thData->civilianEnemy4th->GetPosition().x;
	int deltaY = this->mPlayer->GetPosition().y - this->mCivilianEnemy4thData->civilianEnemy4th->GetPosition().y;
	if (abs(deltaX) <= 150 && abs(deltaY) <= 30)
	{
		return true;
	}
	return false;

}

bool CivilianEnemy4th::IsInAttackRange()
{
	int deltaX = abs(this->mCivilianEnemy4thData->civilianEnemy4th->mPlayer->GetPosition().x - this->mCivilianEnemy4thData->civilianEnemy4th->GetPosition().x);
	int deltaY = abs(this->mCivilianEnemy4thData->civilianEnemy4th->mPlayer->GetPosition().y - this->mCivilianEnemy4thData->civilianEnemy4th->GetPosition().y);
	if (deltaX <= 40&&abs(deltaY)<=40)
		return true;
	return false;
}

void CivilianEnemy4th::SetState(CivilianEnemy4thState * newState)
{
	delete this->mCivilianEnemy4thData->state;
	this->mCivilianEnemy4thData->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();
}

CivilianEnemy4thState::StateName CivilianEnemy4th::GetState()
{
	return mCurrentState;
}

void CivilianEnemy4th::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);

}

void CivilianEnemy4th::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(), transform);
}

RECT CivilianEnemy4th::GetBound()
{
	RECT rect;

	rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight();
	rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight();

	return rect;
}

void CivilianEnemy4th::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

	if (this->mCivilianEnemy4thData->state)
		this->mCivilianEnemy4thData->state->OnCollision(impactor, data, side);
	if (this->HP <= 0)
	{
		this->isDestroy = true;
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.15f, NULL);
	}
	if (this->HP <= 0)
	{
		this->isDestroy = true;
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.15f, NULL);
		Sound::getInstance()->play("BalloonPop", false, 1);
	}

}

Animation *CivilianEnemy4th::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

Animation * CivilianEnemy4th::GetAnimation(CivilianEnemy4thState::StateName state)
{
	switch (state)
	{
	case CivilianEnemy4thState::Stand:
		return mAnimationStand;
		break;
	case CivilianEnemy4thState::Beat:
		return mAnimationBeat;
		break;
	case CivilianEnemy4thState::Run:
		return mAnimationRun;
		break;
	}
}

void CivilianEnemy4th::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}


void CivilianEnemy4th::changeAnimation(CivilianEnemy4thState::StateName state)
{
	switch (state)
	{
	case CivilianEnemy4thState::Stand:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::CIVILIANENEMIES, "CivilianEnemy4thStand", 6, 0.4f, NULL);
		break;
	case CivilianEnemy4thState::Beat:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::CIVILIANENEMIES, "CivilianEnemy4thBeat", 4, 0.2f, NULL);
		break;
	case CivilianEnemy4thState::Run:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::CIVILIANENEMIES, "CivilianEnemy4thRun", 12, 0.2f, NULL);
		break;
	
	}
}
void CivilianEnemy4th::OnSetPosition(D3DXVECTOR3 pos)
{
	mCurrentAnimation->SetPosition(pos);
}