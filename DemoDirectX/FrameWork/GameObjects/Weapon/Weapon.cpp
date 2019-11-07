#include "Weapon.h"
#include "../../GameComponents/GameGlobal.h"


Weapon::Weapon()
{
	mAnimation = new Animation(eID::ALADDIN, "apple", 1, 0.15f, NULL);
	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
}

Weapon::~Weapon()
{

}

bool Weapon::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::AppleAladdin;

	mAnimation = new Animation(eID::ALADDIN, "apple", 1, 1.0f, NULL);

	//________________________________________________________
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
	return true;

}

Weapon::Weapon(D3DXVECTOR2 position)
{
	init(D3DXVECTOR3(position.x, position.y, 0));
}
Weapon::Weapon(D3DXVECTOR3 position)
{
	init(position);
}
void Weapon::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void Weapon::Update(float dt)
{
	mAnimation->Update(dt);
	this->AddVy(2.0f);
	Entity::Update(dt);
	if (mAnimation->mCurrentIndex == 5) isDeleted = true;
}

void Weapon::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void Weapon::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->SetVx(0);
	this->SetVy(0);
	if (isDestroy == false)
	{
		isDestroy = true;
		delete mAnimation;
		mAnimation = new Animation(eID::ALADDIN, "appledestroy", 5, 0.05f, NULL);
	}
}

void Weapon::Draw(D3DXVECTOR3 transform)
{

}
void Weapon::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(1, 1), transform);
}
