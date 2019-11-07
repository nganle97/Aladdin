#include "Camel.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/GameCollision.h"

Camel::Camel()
{

}

Camel::~Camel()
{

}

bool Camel::init(D3DXVECTOR3 position, GameMap* gameMap)
{
	this->Tag = Entity::EntityTypes::Camel;
	mAnimation = new Animation(eID::ALADDINSP,"Camel",1,0.1,NULL);
	isDestroy = false;
	SetPosition(position);
	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(5);
	this->gameMap = gameMap;
	return true;
}

Camel::Camel(D3DXVECTOR3 position,GameMap* gameMap)
{
	init(position,gameMap);
}

Camel::Camel(D3DXVECTOR2 position,GameMap *gameMap)
{
	init(D3DXVECTOR3(position.x, position.y, 0),gameMap);
}


void Camel::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void Camel::Update(float dt)
{
	if (this->isDestroy == true)
	{
		delete mAnimation;
		mAnimation = new Animation(eID::ALADDINSP, "CamelAttack", 6, 0.2f, NULL);
		isDestroy = false;
	}
	if (mAnimation->mCurrentIndex == 6 && canThrow == false)
	{
		delete mAnimation;
		mAnimation = new Animation(eID::ALADDINSP, "Camel", 1, 0.1f, NULL);
	}
	if (mAnimation->mCurrentIndex == 6)
	{
		if (canThrow == true)
		{
			class Apple* tmp = new class Apple(D3DXVECTOR2(this->posX + 90, this->posY - 20), true);
			tmp->SetVx(125.0f);
			this->gameMap->InsertAppleAladdin(tmp);
		}
		canThrow = false;
	}
	mAnimation->Update(dt);



}

void Camel::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void Camel::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	canThrow = true;


}

void Camel::Draw(D3DXVECTOR3 transform)
{

}
void Camel::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}

RECT Camel::GetBound()
{

	RECT bound;
	bound.left = this->GetPosition().x - this->GetWidth() / 4;
	bound.right = bound.left + this->GetWidth()/2;
	bound.top = this->GetPosition().y - mAnimation->GetSprite()->GetHeight();
	bound.bottom = bound.top+ mAnimation->GetSprite()->GetHeight();
	return bound;
}