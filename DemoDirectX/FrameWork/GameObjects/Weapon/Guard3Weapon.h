#pragma once

#include "../../GameComponents/Animation.h"
#include "../Entity.h"
//vien gach
class Guard3Weapon : public Entity
{
public:


	~Guard3Weapon();
	Guard3Weapon();
	Guard3Weapon(D3DXVECTOR3 position);
	Guard3Weapon(D3DXVECTOR2 position);
	Guard3Weapon(float x,float y, D3DXVECTOR2 velocityX_Y, D3DXVECTOR2 acceleratorX_Y);
	void Update(float dt);

	RECT GetBound();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR3 transform);

	void Draw(D3DXVECTOR2 transform);

	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
protected:


	bool init(D3DXVECTOR3 position);
	bool init(D3DXVECTOR3 position,D3DXVECTOR2 velocityX_Y, D3DXVECTOR2 acceleratorX_Y);
	void OnSetPosition(D3DXVECTOR3 poks);
	Animation *mAnimation;
	float accelatorX;
	float accelatorY;
};
