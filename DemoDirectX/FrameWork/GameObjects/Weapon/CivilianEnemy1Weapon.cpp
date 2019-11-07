#include "CivilianEnemy1Weapon.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/GameCollision.h"

CivilianEnemy1Weapon::CivilianEnemy1Weapon()
{
	mAnimation = new Animation(eID::CIVILIANENEMIES, "CivilianEnemy1stWeapon", 6, 0.15f, NULL);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());

}

CivilianEnemy1Weapon::~CivilianEnemy1Weapon()
{

}

bool CivilianEnemy1Weapon::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::EnemiesWeapon;

	mAnimation = new Animation(eID::CIVILIANENEMIES, "CivilianEnemy1stWeapon", 6, 0.2f, NULL);

	//________________________________________________________
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
	Vy = 3.0f;
	return true;
}


CivilianEnemy1Weapon::CivilianEnemy1Weapon(D3DXVECTOR2 position)
{
	init(D3DXVECTOR3(position.x, position.y, 0));
}


CivilianEnemy1Weapon::CivilianEnemy1Weapon(D3DXVECTOR3 position)
{
	init(position);
	this->SetVy(10.0f);
}
void CivilianEnemy1Weapon::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void CivilianEnemy1Weapon::Update(float dt)
{
	mAnimation->Update(dt);

	Entity::Update(dt);
	this->AddVy(Vy);
	if (mAnimation->mCurrentIndex == mAnimation->mTotalFrame&&isDestroy==true) isDeleted = true;
}

void CivilianEnemy1Weapon::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void CivilianEnemy1Weapon::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::Ground:
	case Entity::EntityTypes::Guard1:
	case Entity::EntityTypes::Guard2:
	case Entity::EntityTypes::Guard3:
	case Entity::EntityTypes::HorizontalRope:
	case Entity::EntityTypes::Stair1:
	case Entity::EntityTypes::Stair2:
	case Entity::EntityTypes::VerticalRope:

		this->SetVx(0);
		this->SetVy(0);
		if (isDestroy == false)
		{
			isDestroy = true;
			delete mAnimation;
			mAnimation = new Animation(eID::CIVILIANENEMIES, "CivilianEnemy1stWeaponDestroy", 8, 0.05f, NULL);
			Sound::getInstance()->play("BodyCrunch", false, 1);
		}
		break;
	case Entity::EntityTypes::Aladdin:
		if (impactor->IsMakeDamage() == true && GameCollision::isCollide(impactor->GetBoundWeapon(), this->GetBound()) == true)
		{
			isDestroy = true;
			this->SetVy(0);
			this->Vy = 0;
			this->SetVx(0);
			delete mAnimation;
			mAnimation = new Animation(eID::EXPLOSION, "Explosion3rd", 5, 0.15f, NULL);
		}
	default:
		return;
	}
}

void CivilianEnemy1Weapon::Draw(D3DXVECTOR3 transform)
{

}
void CivilianEnemy1Weapon::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}
RECT CivilianEnemy1Weapon::GetBound()
{
	RECT rect;

	rect.left = this->posX - mAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mAnimation->GetSprite()->GetHeight();
	rect.bottom = rect.top + mAnimation->GetSprite()->GetHeight();

	return rect;
}