#pragma once

#include "../../GameComponents/Animation.h"
#include "../Entity.h"
//vien gach
class CivilianEnemy1Weapon : public Entity
{
public:


	~CivilianEnemy1Weapon();
	CivilianEnemy1Weapon();
	CivilianEnemy1Weapon(D3DXVECTOR3 position);
	CivilianEnemy1Weapon(D3DXVECTOR2 position);
	void Update(float dt);

	RECT GetBound();
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR3 transform);

	void Draw(D3DXVECTOR2 transform);

	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
protected:

	float Vy;
	bool init(D3DXVECTOR3 position);
	void OnSetPosition(D3DXVECTOR3 poks);
	Animation *mAnimation;
};
