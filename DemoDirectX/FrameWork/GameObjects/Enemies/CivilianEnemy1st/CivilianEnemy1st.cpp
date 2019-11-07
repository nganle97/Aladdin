#include "CivilianEnemy1st.h"

CivilianEnemy1st::CivilianEnemy1st()
{

	this->Tag = Entity::CivilianEnemy1st;
	this->mCivilianEnemy1stData = new CivilianEnemy1stData();
	this->mCivilianEnemy1stData->civilianEnemy1st = this;
	mCurrentAnimation = new Animation();
	this->mCivilianEnemy1stData->civilianEnemy1st->SetState(new CivilianEnemy1stThrowState(this->mCivilianEnemy1stData));
}

CivilianEnemy1st::CivilianEnemy1st(D3DXVECTOR2 position, Player* mplayer)
{
	this->Tag = Entity::CivilianEnemy1st;
	this->HP = 1;
	this->mCivilianEnemy1stData = new CivilianEnemy1stData();
	this->mCivilianEnemy1stData->civilianEnemy1st = this;
	mCurrentAnimation = new Animation();
	this->mCivilianEnemy1stData->civilianEnemy1st->SetState(new CivilianEnemy1stThrowState(this->mCivilianEnemy1stData));
	this->SetPosition(position);
	this->mPlayer = mplayer;	
	this->GetCurrentAnimation()->GetSprite()->SetAnchorPoint(0, 0);
}

CivilianEnemy1st::~CivilianEnemy1st()
{

}

void CivilianEnemy1st::Update(float dt)
{
	if (this->mCurrentAnimation->mCurrentIndex == this->mCurrentAnimation->mTotalFrame&&isDestroy == true)
		isDeleted = true;
	if (IsNearToPlayer() == true)
	{
		
		mCurrentAnimation->Update(dt);

		if (this->mCivilianEnemy1stData->state)
		{
			this->mCivilianEnemy1stData->state->Update(dt);
		}

		Entity::Update(dt);
		
	}
	else
	{
		this->mCivilianEnemy1stData->civilianEnemy1st->SetState(new CivilianEnemy1stThrowState(mCivilianEnemy1stData));
		this->GetCurrentAnimation()->GetSprite()->SetAnchorPoint(0, 0);
	}
	
}

bool CivilianEnemy1st::IsNearToPlayer()
{
	int deltaX = this->mPlayer->GetPosition().x - this->mCivilianEnemy1stData->civilianEnemy1st->GetPosition().x;
	int deltaY = this->mPlayer->GetPosition().y - this->mCivilianEnemy1stData->civilianEnemy1st->GetPosition().y;
	if (abs(deltaX) <= 70 && deltaY >0&&deltaY<200)
	{
		return true;
	}
	return false;

}

void CivilianEnemy1st::SetState(CivilianEnemy1stState * newState)
{
	delete this->mCivilianEnemy1stData->state;
	this->mCivilianEnemy1stData->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();
}

CivilianEnemy1stState::StateName CivilianEnemy1st::GetState()
{
	return mCurrentState;
}

void CivilianEnemy1st::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (IsNearToPlayer() == true)
	{
		mCurrentAnimation->SetPosition(this->GetPosition());
		mCurrentAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
	}
}
void CivilianEnemy1st::Draw(D3DXVECTOR2 transform)
{
	if (IsNearToPlayer() == true)
	{
		mCurrentAnimation->SetPosition(this->GetPosition());
		mCurrentAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(), transform);
	}
}

RECT CivilianEnemy1st::GetBound()
{
	/*RECT rect;

	rect.left = this->posX + mCurrentAnimation->GetSprite()->GetWidth()/2;
	rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
	rect.top = this->posY + mCurrentAnimation->GetSprite()->GetHeight()/2;
	rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight();

	return rect;*/
	POINT tmp = this->mCivilianEnemy1stData->civilianEnemy1st->GetCurrentAnimation()->GetAnchorPoint();
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
		{
			rect.left = this->posX - tmp.x;
			rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
		}
		rect.top = this->posY - tmp.y;
		rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight();
	}
	return rect;
}

void CivilianEnemy1st::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

	switch (impactor->Tag)
	{
	case Entity::Aladdin:
		if (impactor->IsMakeDamage()==true&&GameCollision::isCollide(impactor->GetBoundWeapon(),this->GetBound())==true)
			this->TakeDamage(1);
		break;
	}
	if (this->HP <= 0)
	{
		this->isDestroy = true;
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.15f, NULL);
		Sound::getInstance()->play("BalloonPop", false, 1);
	}
}

Animation *CivilianEnemy1st::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

Animation * CivilianEnemy1st::GetAnimation(CivilianEnemy1stState::StateName state)
{
	switch (state)
	{
	case CivilianEnemy1stState::Throw:
		return mAnimationThrow;
	default:
		break;
	}
}


void CivilianEnemy1st::changeAnimation(CivilianEnemy1stState::StateName state)
{
	switch (state)
	{
	case CivilianEnemy1stState::Throw:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::CIVILIANENEMIES, "CivilianEnemy1st", 10, 0.2f, NULL);
		break;
	default:
		break;
	}
}
void CivilianEnemy1st::OnSetPosition(D3DXVECTOR3 pos)
{
	mCurrentAnimation->SetPosition(pos);
}
void CivilianEnemy1st::SetGameMap(GameMap *gamemap)
{
	this->mGameMap = gamemap;
}

GameMap* CivilianEnemy1st::getGameMap()
{
	return this->mGameMap;
}