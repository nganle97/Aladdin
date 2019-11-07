#include "SpringBoard.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/GameCollision.h"

SpringBoard::SpringBoard()
{

}

SpringBoard::~SpringBoard()
{

}

bool SpringBoard::init(D3DXVECTOR3 position)
{
	this->Tag = Entity::EntityTypes::SpringBoard;
	mAnimation = new Animation(eID::ALADDINSP, "SpringBoard", 1, 0.1, NULL);
	isDestroy = false;
	SetPosition(position);
	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(5);
	return true;
}

SpringBoard::SpringBoard(D3DXVECTOR3 position)
{
	init(position);
}
SpringBoard::SpringBoard(D3DXVECTOR2 position)
{
	init(D3DXVECTOR3(position.x, position.y, 0));
}


void SpringBoard::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void SpringBoard::Update(float dt)
{
	if (mAnimation->mCurrentIndex == 5)
	{
		delete mAnimation;
		mAnimation = new Animation(eID::ALADDINSP, "SpringBoard", 1, 0.1f, NULL);
		//isDestroy = false;
	}
	mAnimation->Update(dt);



}

void SpringBoard::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void SpringBoard::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->GetVy() > 0)
	{
		delete mAnimation;
		mAnimation = new Animation(eID::ALADDINSP, "SpringBoardAction", 5, 0.1f, NULL);
		Sound::getInstance()->play("Flagpole", false, 1);
	}
}

void SpringBoard::Draw(D3DXVECTOR3 transform)
{

}
void SpringBoard::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}

RECT SpringBoard::GetBound()
{
	POINT tmp = mAnimation->GetAnchorPoint();
	RECT bound;
	bound.left = this->GetPosition().x + this->GetWidth()/4 ;
	bound.right = bound.left + this->GetWidth()*3/4 ;
	bound.top = this->GetPosition().y - tmp.y;
	bound.bottom = bound.top + mAnimation->GetSprite()->GetHeight() ;
	return bound;
}