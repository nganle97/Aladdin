#include "JafarWeapon2.h"
#include "../../GameComponents/GameGlobal.h"


JafarWeapon2::JafarWeapon2()
{
	mAnimation = new Animation(eID::JAFAR, "BigFire", 8, 0.15f, NULL);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
}

JafarWeapon2::~JafarWeapon2()
{

}

bool JafarWeapon2::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::JafarWeapon2;

	mAnimation = new Animation(eID::JAFAR, "BigFire", 8, 0.2f, NULL);

	//________________________________________________________
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());

	return true;
}


JafarWeapon2::JafarWeapon2(D3DXVECTOR2 position, Player* player)
{
	this->player = player;
	this->accelatorX = 5.0f;
	this->accelatorY = 5.0f;
	init(D3DXVECTOR3(position.x, position.y, 0));
	if (position.x < player->GetPosition().x)
	{
		this->SetVx(80.0f);
		this->mAnimation->SetFlipHorizontal(false);
	}
	else if (position.x > player->GetPosition().x)
	{
		this->SetVx(-80.0f);
		this->mAnimation->SetFlipHorizontal(true);
	}
}


JafarWeapon2::JafarWeapon2(D3DXVECTOR3 position, Player* player)
{
	this->player = player;
	this->accelatorX = 5.0f;
	this->accelatorY = 5.0f;
	init(position);

}
void JafarWeapon2::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);

}

void JafarWeapon2::Update(float dt)
{
	mAnimation->Update(dt);
	this->AddVy(accelatorY);
	Entity::Update(dt);
	if ((mAnimation->mCurrentIndex == 5 && isDestroy == true)||abs(this->player->GetPosition().x-posX)>1000) isDeleted = true;
}

void JafarWeapon2::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void JafarWeapon2::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

	switch (impactor->Tag)
	{
	case Entity::EntityTypes::Ground:
		accelatorY = 0;
		this->SetVy(0);
		
		break;
	default:
		return;
	}
}

void JafarWeapon2::Draw(D3DXVECTOR3 transform)
{

}
void JafarWeapon2::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}
RECT JafarWeapon2::GetBound()
{
	RECT rect;

	rect.left = this->posX - mAnimation->GetSprite()->GetWidth() /4 ;
	rect.right = rect.left + mAnimation->GetSprite()->GetWidth()/2;
	rect.top = this->posY - mAnimation->GetSprite()->GetHeight()/2;
	rect.bottom = rect.top + mAnimation->GetSprite()->GetHeight()/2;

	return rect;
}