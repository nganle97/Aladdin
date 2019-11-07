/*
#include "Enemy.h"

Enemy::Enemy()
{
	Tag = Entity::EntityTypes::Enemy;
	this->HP = 1;
}

D3DXVECTOR3 Enemy::GetPosition()
{
	return Entity::GetPosition();
}
void Enemy::Draw(D3DXVECTOR2 trans)
{

}

RECT Enemy::GetBound()
{
	return Entity::GetBound();
}
Rect Enemy::GetRect()
{
	return Entity::GetRect();
}

void Enemy::OnCollision(Entity *impactor, CollisionReturn data, Entity::SideCollisions side)
{
	Entity::OnCollision(impactor, data, side);
}


void Enemy::SetHealth(int hp)
{
	Entity::SetHealth(hp);
}

void Enemy::TakeDamage(int Damage)
{
	Entity::TakeDamage(Damage);
}
void Enemy::SetTimeImmortal(float timeImmortal)
{
	Entity::SetTimeImmortal(timeImmortal);
}

void Enemy::OnSetPosition(D3DXVECTOR3 pos)
{

}

void Enemy::Update(float dt)
{
	Entity::Update(dt);
}

void Enemy::SetPosition(float x, float y)
{
	Entity::SetPosition(D3DXVECTOR2(x, y));
}

void Enemy::SetPosition(D3DXVECTOR2 pos)
{
	Entity::SetPosition(D3DXVECTOR3(pos.x, pos.y, 0));
}

void Enemy::SetPosition(D3DXVECTOR3 pos)
{
	Entity::SetPosition(pos);

}

void Enemy::AddPosition(D3DXVECTOR3 pos)
{
	Entity::AddPosition(pos);
}

void Enemy::AddPosition(D3DXVECTOR2 pos)
{
	Entity::AddPosition(D3DXVECTOR3(pos));
}

void Enemy::AddPosition(float x, float y)
{
	Entity::AddPosition(D3DXVECTOR3(x, y, 0));
}

void Enemy::SetWidth(int width)
{
	Entity::SetWidth(width);
}

int Enemy::GetWidth()
{
	return Entity::GetWidth();
}

void Enemy::SetHeight(int height)
{
	Entity::SetHealth(height);
}

int Enemy::GetHeight()
{
	return Entity::GetHeight();
}

float Enemy::GetVx()
{
	return Entity::GetVx();
}

void Enemy::SetVx(float vx)
{
	Entity::SetVx(vx);
}

void Enemy::AddVx(float vx)
{
	Entity::AddVx(vx);
}

float Enemy::GetVy()
{
	return Entity::GetVy();
}

void Enemy::SetVy(float vy)
{
	Entity::SetVy(vy);
}

void Enemy::AddVy(float vy)
{
	Entity::AddVy(vy);
}

Entity::FaceDirection Enemy::getFaceDirection()
{
	return Entity::getFaceDirection();
}
*/