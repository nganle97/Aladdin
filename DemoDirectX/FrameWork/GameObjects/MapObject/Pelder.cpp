#include "Pelder.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/GameCollision.h"

Pelder::Pelder()
{

}

Pelder::~Pelder()
{

}

bool Pelder::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::Items;
	_pelder = new Animation(eID::ALADDINSP, "Pelder", 7, 0.25, NULL);
	_store = new Animation(eID::ALADDINSP, "Store", 1, 0.1, NULL);
	isDrawPelder = true;
	SetPosition(position);
	Entity::SetWidth(_pelder->GetSprite()->GetWidth());
	Entity::SetHeight((_pelder->GetSprite()->GetHeight()));
	return true;
}

Pelder::Pelder(D3DXVECTOR3 position)
{
	init(position);
}
Pelder::Pelder(D3DXVECTOR2 position)
{
	init(D3DXVECTOR3(position.x, position.y, 0));
}


void Pelder::OnSetPosition(D3DXVECTOR3 pos)
{
	_pelder->SetPosition(pos);
}

void Pelder::Update(float dt)
{
	if (isDrawPelder==true)
	_pelder->Update(dt);
	if (isDrawStore == true) _store->Update(dt);

	if (_store->mCurrentIndex ==25) isDrawPelder = true;
}

void Pelder::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (isDrawPelder == true)
	_pelder->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void Pelder::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (_store->mTotalFrame == 1)
{
	isDrawStore = true;
	_store = new Animation(eID::ALADDINSP, "Store", 30, 0.25f, NULL);
	Sound::getInstance()->play("PelderShop", false, 1);
	_store->SetStop(true);
	_pelder->mTotalFrame = 14;
	_pelder->mCurrentIndex = 1;
	isDrawPelder = false;
}

}

void Pelder::Draw(D3DXVECTOR3 transform)
{

}
void Pelder::Draw(D3DXVECTOR2 transform)
{
	if (isDrawPelder == true)
	_pelder->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
	if (isDrawStore == true)
	{
		_store->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
	}
}

RECT Pelder::GetBound()
{

	RECT bound;
	bound.left = this->GetPosition().x - this->GetWidth() / 4;
	bound.right = bound.left + this->GetWidth() / 2;
	bound.top = this->GetPosition().y - _pelder->GetSprite()->GetHeight() / 2;
	bound.bottom = bound.top + _pelder->GetSprite()->GetHeight() / 2;
	return bound;
}