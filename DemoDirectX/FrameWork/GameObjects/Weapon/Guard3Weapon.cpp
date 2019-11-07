#include "Guard3Weapon.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/GameCollision.h"


Guard3Weapon::Guard3Weapon()
{
	mAnimation = new Animation(eID::GUARDS, "Guard3rdWeapon", 7, 0.2f, NULL);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
}

Guard3Weapon::~Guard3Weapon()
{

}

bool Guard3Weapon::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::EnemiesWeapon;

	mAnimation = new Animation(eID::GUARDS, "Guard3rdWeapon", 7, 0.2f, NULL);

	//________________________________________________________
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
	return true;
}
bool Guard3Weapon::init(D3DXVECTOR3 position,D3DXVECTOR2 velocityX_Y, D3DXVECTOR2 acceleratorX_Y)
{
	init(position);
	this->SetVx(velocityX_Y.x);
	this->SetVy(velocityX_Y.y);
	this->accelatorX = acceleratorX_Y.x;
	this->accelatorY = acceleratorX_Y.y;
	return true;
}

Guard3Weapon::Guard3Weapon(D3DXVECTOR2 position)
{
	init(D3DXVECTOR3(position.x, position.y, 0));
}

Guard3Weapon::Guard3Weapon(float x, float y, D3DXVECTOR2 velocityX_Y, D3DXVECTOR2 acceleratorX_Y)
{
	init(D3DXVECTOR3(x, y, 0), velocityX_Y, acceleratorX_Y);
}

Guard3Weapon::Guard3Weapon(D3DXVECTOR3 position)
{
	init(position);
}
void Guard3Weapon::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void Guard3Weapon::Update(float dt)
{
	mAnimation->Update(dt);

	Entity::Update(dt);
		//this->AddVx(accelatorX);
		this->AddVy(accelatorY);
}

void Guard3Weapon::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void Guard3Weapon::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::CivilianEnemy1st:
	case Entity::EntityTypes::CivilianEnemy2nd:
	case Entity::EntityTypes::CivilianEnemy4th:
	case Entity::EntityTypes::EnemiesWeapon:
	case Entity::EntityTypes::Ground:
	case Entity::EntityTypes::AppleAladdin:
	case Entity::EntityTypes::Stair1:
	case Entity::EntityTypes::Stair2:
		isDeleted = true;
		break;
	case Entity::EntityTypes::Aladdin:
		if (impactor->IsMakeDamage() == true&& GameCollision::isCollide(impactor->GetBoundWeapon(), this->GetBound()) == true)
		{
				if (accelatorX <= 0) this->SetVx(70.0f);
				else  this->SetVx(-70.0f);
				this->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY*1.4);
				this->accelatorY = 2.5f;
				return;
		}
		else
		{
			if (GameCollision::isCollide(impactor->GetBoundBody(), this->GetBound()) == true)
			{
				isDeleted = true;
				Sound::getInstance()->play("SwordSpinning", false, 1);
				return;
			}
			
		}
	default:
		return;
	}
}

void Guard3Weapon::Draw(D3DXVECTOR3 transform)
{

}
void Guard3Weapon::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}
RECT Guard3Weapon::GetBound()
{
	RECT rect;

	rect.left = this->posX - mAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mAnimation->GetSprite()->GetHeight();
	rect.bottom = rect.top + mAnimation->GetSprite()->GetHeight();

	return rect;
}