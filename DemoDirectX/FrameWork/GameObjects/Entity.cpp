#include "Entity.h"

Entity::Entity()
{
	Tag = None;
	this->HP = 1;
}

D3DXVECTOR3 Entity::GetPosition()
{
	return D3DXVECTOR3(posX, posY, 0);
}
void Entity::Draw(D3DXVECTOR2 trans)
{

}


RECT Entity::GetBound()
{
	RECT bound;
	
	bound.left = posX - width / 2;
	bound.right = posX + width / 2;
	bound.top = posY - height / 2;
	bound.bottom = posY + height / 2;
	
	return bound;
}
RECT Entity::GetBoundBody()
{
	RECT bound=RECT();

	return bound;
}

RECT Entity::GetBoundWeapon()
{
	RECT bound = RECT();;

	return bound;
}



void Entity::OnCollision(Entity *impactor, CollisionReturn data, Entity::SideCollisions side)
{
	vx = 0, vy = 0;
}
void Entity::OnCollision(Entity *impactor, CollisionReturn data)
{
	vx = 0, vy = 0;
}

void Entity::SetHealth(int hp)
{
	HP = hp;
}

int Entity::GetHealth()
{
	return this->HP;
}

void Entity::TakeDamage(int Damage)
{
	HP -= Damage;
}
void Entity::SetTimeImmortal(float timeImmortal)
{
	this->timeImmortal = timeImmortal;
}
float Entity::GetTimeImmortal()
{
	return this->timeImmortal;
}

void Entity::OnSetPosition(D3DXVECTOR3 pos)
{

}

void Entity::Update(float dt)
{
	posX += vx*dt;
	posY += vy*dt;
	if (timeImmortal > 0) timeImmortal -= dt;
}

void Entity::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR2(x, y));
}

void Entity::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR3(pos.x, pos.y, 0));
}

void Entity::SetPosition(D3DXVECTOR3 pos)
{
	posX = pos.x;
	posY = pos.y;
	OnSetPosition(pos);

}

void Entity::AddPosition(D3DXVECTOR3 pos)
{
	this->SetPosition(this->GetPosition() + pos);
}

void Entity::AddPosition(D3DXVECTOR2 pos)
{
	AddPosition(D3DXVECTOR3(pos));
}

void Entity::AddPosition(float x, float y)
{
	AddPosition(D3DXVECTOR3(x, y, 0));
}

void Entity::SetWidth(int width)
{
	this->width = width;
}

int Entity::GetWidth()
{
	return width;
}

void Entity::SetHeight(int height)
{
	this->height = height;
}

int Entity::GetHeight()
{
	return height;
}

float Entity::GetVx()
{
	return vx;
}

void Entity::SetVx(float vx)
{
	this->vx = vx;
}

void Entity::AddVx(float vx)
{
	this->vx += vx;
}

float Entity::GetVy()
{
	return vy;
}

void Entity::SetVy(float vy)
{
	this->vy = vy;
}

void Entity::AddVy(float vy)
{
	this->vy += vy;
}
bool Entity::IsDeleted()
{
	return this->isDeleted;
}

void Entity::SetDelete(bool flag)
{
	isDeleted=flag;
}

bool Entity::IsDestroy()
{
	return this->isDestroy;
}

void Entity::SetDestroy(bool flag)
{
	isDestroy = flag;
}

bool Entity::IsDraw()
{
	return this->isDraw;
}

void Entity::SetDraw(bool flag)
{
	isDraw = flag;
}

Entity::FaceDirection Entity::getFaceDirection()
{
	return faceDirection;
}

bool Entity::IsMakeDamage()
{
	return this->isMakeDamage;
}

void Entity::SetMakeDamage(bool flag)
{
	isMakeDamage = flag;
}