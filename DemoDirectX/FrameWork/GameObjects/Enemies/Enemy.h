/*
#pragma once
#include "../../GameObjects/Entity.h"
class Enemy :public Entity
{
	Enemy();

	enum EnemyTypes
	{
		Guard1st,
		Guard2nd,
		Guard3rd,
		CivilianEnemy1st,
		CivilianEnemy2nd,
		CivilianEnemy4th,
		Boss_Jafar
	};
	virtual void Draw(D3DXVECTOR2 trans);

	virtual RECT GetBound();

	virtual Rect GetRect();
	virtual FaceDirection getFaceDirection();

	virtual void SetPosition(float x, float y);

	virtual void SetPosition(D3DXVECTOR2 pos);

	virtual void SetPosition(D3DXVECTOR3 pos);

	virtual void AddPosition(D3DXVECTOR3 pos);

	virtual void AddPosition(D3DXVECTOR2 pos);

	virtual void AddPosition(float x, float y);

	virtual void SetWidth(int width);

	virtual int GetWidth();

	virtual void SetHeight(int height);

	virtual int GetHeight();

	virtual float GetVx();

	virtual void SetVx(float vx);

	virtual void AddVx(float vx);

	virtual float GetVy();

	virtual void SetVy(float vy);

	virtual void AddVy(float vy);

	virtual D3DXVECTOR3 GetPosition();

	virtual void Update(float dt);

	virtual void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);

	virtual void SetHealth(int hp);

	virtual void TakeDamage(int Damage);

	virtual void SetTimeImmortal(float timeImmortal);

	Enemy::EnemyTypes EnemyType;
protected:
	virtual void OnSetPosition(D3DXVECTOR3 pos);
};*/