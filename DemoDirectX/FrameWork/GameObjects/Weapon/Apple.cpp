#include "Apple.h"
#include "../../GameComponents/GameGlobal.h"


Apple::Apple()
{
	mAnimation = new Animation(eID::ALADDIN, "apple", 1, 0.15f, NULL);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
}

Apple::~Apple()
{

}

bool Apple::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::AppleAladdin;

	mAnimation = new Animation(eID::ALADDIN, "apple", 1, 1.0f, NULL);

	//________________________________________________________
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
	return true;

}

Apple::Apple(D3DXVECTOR2 position,bool isCamelThrow)
{
	init(D3DXVECTOR3(position.x, position.y, 0));
	if (isCamelThrow == true)
	{
		delete mAnimation;
		mAnimation = new Animation(eID::ALADDINSP, "CamelApple", 1, 1.0f, NULL);
		this->isCamelThrow = true;
	}
}
Apple::Apple(D3DXVECTOR3 position,bool isCamelThrow)
{
	init(position);
	if (isCamelThrow == true)
	{
		delete mAnimation;
		mAnimation = new Animation(eID::ALADDINSP, "CamelApple", 1, 1.0f, NULL);
		this->isCamelThrow = true;
	}
}
void Apple::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void Apple::Update(float dt)
{
	mAnimation->Update(dt);
	if (isCamelThrow==false)
	this->AddVy(2.0f);
	Entity::Update(dt);
	if (mAnimation->mCurrentIndex == 5) isDeleted = true;
}

void Apple::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void Apple::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::CivilianEnemy1st:
	case Entity::EntityTypes::CivilianEnemy2nd:
	case Entity::EntityTypes::CivilianEnemy4th:
	case Entity::EntityTypes::EnemiesWeapon:
	case Entity::EntityTypes::Ground:
	case Entity::EntityTypes::Guard1:
	case Entity::EntityTypes::Guard2:
	case Entity::EntityTypes::Guard3:
	case Entity::EntityTypes::HorizontalRope:
	case Entity::EntityTypes::Stair1:
	case Entity::EntityTypes::Stair2:
	case Entity::EntityTypes::Jafar:
		this->SetVx(0);
		this->SetVy(0);
		if (isDestroy == false)
		{
			isDestroy = true;
			delete mAnimation;
			mAnimation = new Animation(eID::ALADDIN, "appledestroy", 5, 0.05f, NULL);
			Sound::getInstance()->play("AppleSplat", false, 1);
		}
	default:
		return;
	}

}

void Apple::Draw(D3DXVECTOR3 transform)
{

}
void Apple::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(1, 1), transform);
}
RECT Apple::GetBound()
{
	RECT rect;

	rect.left = this->posX - mAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mAnimation->GetSprite()->GetHeight();
	rect.bottom = rect.top + mAnimation->GetSprite()->GetHeight();

	return rect;
}