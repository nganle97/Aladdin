#include "Fire.h"
#include "../../GameComponents/GameGlobal.h"


Fire::Fire()
{
}

Fire::~Fire()
{

}

bool Fire::init(D3DXVECTOR2 position)
{
	this->Tag = Entity::EntityTypes::Flame;

	mAnimation = new Animation(eID::JAFAR, "SmallFire", 5, 0.3f, NULL);

	//________________________________________________________
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
	return true;
}


Fire::Fire(D3DXVECTOR2 position)
{
	init(position);
}

void Fire::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);

}

void Fire::Update(float dt)
{
		mAnimation->Update(dt);
		//Entity::Update(dt);
		if (mAnimation->mCurrentIndex == mAnimation->mTotalFrame) isDeleted = true;
}

void Fire::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void Fire::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::Aladdin:
		this->isDestroy = true;
		return;
	}
}

void Fire::Draw(D3DXVECTOR3 transform)
{

}
void Fire::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}
RECT Fire::GetBound()
{
	RECT rect;

	rect.left = this->posX - mAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mAnimation->GetSprite()->GetHeight();
	rect.bottom = rect.top + mAnimation->GetSprite()->GetHeight();

	return rect;
}