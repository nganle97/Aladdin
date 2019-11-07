#include "FloatingGround.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/GameCollision.h"

FloatingGround::FloatingGround()
{
	mAnimation = new Animation(eID::ALADDINSP, "FloatingGround", 1, 0.15f, NULL);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
}

FloatingGround::~FloatingGround()
{

}

bool FloatingGround::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::FloatingGround;
	RECT tmp; tmp.left = 0; tmp.right = 33; tmp.top = 0; tmp.bottom = 14;
	mAnimation = new Animation(eID::ALADDINSP, "FloatingGround", 1, 0.15f, NULL);
	isDestroy = false;
	SetPosition(position);
	time_Exist = 0.5;
	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
	startPosition = position;
	return true;
}

FloatingGround::FloatingGround(D3DXVECTOR3 position)
{
	init(position);
}
FloatingGround::FloatingGround(D3DXVECTOR2 position)
{
	init(D3DXVECTOR3(position.x,position.y,0));
}


void FloatingGround::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void FloatingGround::Update(float dt)
{

	if (isCollision_with_Aladdin == true)
	{
		time_Exist -= dt;
		if (time_Exist <= 0)
		{
			this->AddPosition(0, 5);
			if (this->GetPosition().y>startPosition.y+4000)
			{
				this->SetPosition(startPosition);
				isCollision_with_Aladdin = false;
				time_Exist = 0.5;
			}
			else {
				int tmp = 0;
			}
		}
	}
	
	

	
}

void FloatingGround::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void FloatingGround::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	Entity::SideCollisions sideCol = GameCollision::getSideCollision(this, data);
	if (sideCol == Entity::SideCollisions::Top|| sideCol == Entity::SideCollisions::TopLeft|| sideCol == Entity::SideCollisions::TopRight)
	{
		isCollision_with_Aladdin = true;
	}

}

void FloatingGround::Draw(D3DXVECTOR3 transform)
{

}
void FloatingGround::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}

RECT FloatingGround::GetBound()
{

	RECT bound;
	bound.left = this->GetPosition().x - this->GetWidth() / 2;
	bound.right = bound.left + this->GetWidth();
	bound.top = this->GetPosition().y - this->GetHeight() / 2;
	bound.bottom = bound.top + this->GetHeight();
	return bound;
}