#include "CivilianEnemy2nd.h"

CivilianEnemy2nd::CivilianEnemy2nd()
{

	this->Tag = Entity::CivilianEnemy2nd;
	this->mCivilianEnemy2ndData = new CivilianEnemy2ndData();
	this->mCivilianEnemy2ndData->civilianEnemy2nd = this;
	mCurrentAnimation = new Animation();
	this->mCivilianEnemy2ndData->civilianEnemy2nd->SetState(new CivilianEnemy2ndThrowState(this->mCivilianEnemy2ndData));
}

CivilianEnemy2nd::CivilianEnemy2nd(D3DXVECTOR2 position, Player* mplayer)
{
	this->Tag = Entity::CivilianEnemy2nd;
	this->HP = 1;
	this->mCivilianEnemy2ndData = new CivilianEnemy2ndData();
	this->mCivilianEnemy2ndData->civilianEnemy2nd = this;
	mCurrentAnimation = new Animation();
	this->mCivilianEnemy2ndData->civilianEnemy2nd->SetState(new CivilianEnemy2ndThrowState(this->mCivilianEnemy2ndData));
	this->SetPosition(position);
	this->mPlayer = mplayer;
}

CivilianEnemy2nd::~CivilianEnemy2nd()
{

}

void CivilianEnemy2nd::Update(float dt)
{
	if (this->mPlayer->GetPosition().x - this->GetPosition().x > 0)
	{
		this->faceDirection == Entity::FaceDirection::RIGHT;
	}
	else this->faceDirection == Entity::FaceDirection::LEFT;
	if (this->mCurrentAnimation->mCurrentIndex == this->mCurrentAnimation->mTotalFrame&&isDestroy == true)
		isDeleted = true;
	mCurrentAnimation->Update(dt);

	if (this->mCivilianEnemy2ndData->state)
	{
		this->mCivilianEnemy2ndData->state->Update(dt);
	}

	Entity::Update(dt);

}

bool CivilianEnemy2nd::IsNearToPlayer()
{
	int deltaX = this->mPlayer->GetPosition().x - this->mCivilianEnemy2ndData->civilianEnemy2nd->GetPosition().x;
	int deltaY = this->mPlayer->GetPosition().y - this->mCivilianEnemy2ndData->civilianEnemy2nd->GetPosition().y;
	if (abs(deltaX) <= 350 && abs(deltaY) <= 100)
	{
		return true;
	}
	return false;

}

void CivilianEnemy2nd::SetState(CivilianEnemy2ndState * newState)
{
	delete this->mCivilianEnemy2ndData->state;
	this->mCivilianEnemy2ndData->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();
}

CivilianEnemy2ndState::StateName CivilianEnemy2nd::GetState()
{
	return mCurrentState;
}

void CivilianEnemy2nd::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);

}
void CivilianEnemy2nd::Draw(D3DXVECTOR2 transform)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(), transform);
}

RECT CivilianEnemy2nd::GetBound()
{/*
	RECT rect;

	rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight();
	rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight();
	return rect;*/
	RECT rect;
	rect.left = this->posX - 6;
	rect.right = this->posX + 6;
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight();
	rect.bottom = this->posY;
	return rect;
}

void CivilianEnemy2nd::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

	switch (impactor->Tag)
	{
	case Entity::Aladdin:
		if (impactor->IsMakeDamage() == true && GameCollision::isCollide(impactor->GetBoundWeapon(), this->GetBound()) == true)

		{
			this->TakeDamage(1);
			this->SetTimeImmortal(1);
		}
		break;
	case Entity::AppleAladdin:
		if (impactor->IsDestroy() == false)
			this->TakeDamage(1);
		break;
	}
	if (this->HP <= 0)
	{
		this->isDestroy = true;
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.15f, NULL);
	}

}

Animation *CivilianEnemy2nd::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

Animation * CivilianEnemy2nd::GetAnimation(CivilianEnemy2ndState::StateName state)
{
	switch (state)
	{
	case CivilianEnemy2ndState::Throw:
		return mAnimationThrow;
	default:
		break;
	}
}

void CivilianEnemy2nd::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}


void CivilianEnemy2nd::changeAnimation(CivilianEnemy2ndState::StateName state)
{
	switch (state)
	{
	case CivilianEnemy2ndState::Throw:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::CIVILIANENEMIES, "CivilianEnemy2nd", 11, 0.2f, NULL);
		break;
	default:
		break;
	}
}
void CivilianEnemy2nd::OnSetPosition(D3DXVECTOR3 pos)
{
	mCurrentAnimation->SetPosition(pos);
}
void CivilianEnemy2nd::SetGameMap(GameMap *gamemap)
{
	this->mGameMap = gamemap;
}

GameMap* CivilianEnemy2nd::getGameMap()
{
	return this->mGameMap;
}