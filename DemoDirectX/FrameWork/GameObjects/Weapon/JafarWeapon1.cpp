#include "JafarWeapon1.h"
#include "../../GameComponents/GameGlobal.h"


JafarWeapon::JafarWeapon()
{
	mAnimation = new Animation(eID::JAFAR, "SmallFire", 5, 0.15f, NULL);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
}

JafarWeapon::~JafarWeapon()
{

}

bool JafarWeapon::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::JafarWeapon1;

	mAnimation = new Animation(eID::JAFAR, "Star", 3, 0.2f, NULL);

	//________________________________________________________
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());

	this->SetVy(100.0f);
	this->SetVx(100.0f);
	return true;
}


JafarWeapon::JafarWeapon(D3DXVECTOR2 position, Player* player)
{
	this->player = player;
	this->accelatorX = 5.0f;
	this->accelatorY = 5.0f;
	init(D3DXVECTOR3(position.x, position.y, 0));

}


JafarWeapon::JafarWeapon(D3DXVECTOR3 position, Player* player)
{
	this->player = player;
	this->accelatorX = 5.0f;
	this->accelatorY = 5.0f;
	init(position);

}
void JafarWeapon::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
	
}

void JafarWeapon::Update(float dt)
{
	if (this->mAnimation->mCurrentIndex == mAnimation->mTotalFrame&&isDestroy == true)
		isDeleted = true;
	mAnimation->Update(dt);
	{
		timeUpdate = 1;
		if (player->GetPosition().x > this->GetPosition().x)
		{
			this->SetVx(abs(this->GetVx()));
		}
		else (this->SetVx(-abs(this->GetVx())));

		if (player->GetPosition().y-player->GetHeight()/2 > this->GetPosition().y)
		{
			this->SetVy(abs(this->GetVy()));
		}
		else (this->SetVy(-abs(this->GetVy())));
	}
	Entity::Update(dt);
	if (mAnimation->mCurrentIndex == 5&&isDestroy==true) isDeleted = true;
}

void JafarWeapon::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void JafarWeapon::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	
	switch (impactor->Tag)
	{
	case Entity::EntityTypes::Aladdin:
		this->SetVx(0);
		this->SetVy(0);
		if (isDestroy == false)
		{
			D3DXVECTOR2 positionPlayer = D3DXVECTOR2(player->GetPosition().x, player->GetPosition().y - player->GetHeight() / 2);
			D3DXVECTOR2 positionChange=D3DXVECTOR2(0,0);
			if (this->posX > positionPlayer.x) positionChange.x = 7; else positionChange.x = -7;
			player->AddPosition(positionChange);
			//player->AddVx(positionChange.x);

			isDestroy = true;
			delete mAnimation;
			mAnimation = new Animation(eID::JAFAR, "StarDestroy", 3, 0.05f, NULL);
		}
		break;
	default:
		return;
	}
}

void JafarWeapon::Draw(D3DXVECTOR3 transform)
{

}
void JafarWeapon::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}
RECT JafarWeapon::GetBound()
{
	RECT rect;

	rect.left = this->posX - mAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mAnimation->GetSprite()->GetHeight();
	rect.bottom = rect.top + mAnimation->GetSprite()->GetHeight();

	return rect;
}