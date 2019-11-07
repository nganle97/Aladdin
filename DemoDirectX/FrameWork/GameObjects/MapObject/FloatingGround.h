#pragma once

#include "../../GameComponents/Animation.h"
#include "../Entity.h"
//vien gach
class FloatingGround : public Entity
{
public:


	~FloatingGround();
	FloatingGround();
	FloatingGround(D3DXVECTOR3 position);
	FloatingGround(D3DXVECTOR2 position);
	void Update(float dt);


	RECT GetBound();


	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void Draw(D3DXVECTOR3 transform);
	void Draw(D3DXVECTOR2 transform);
	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
protected:

	bool init(D3DXVECTOR3 position);
	void OnSetPosition(D3DXVECTOR3 poks);
	
	Animation* mAnimation;
	float time_Exist;
	bool isCollision_with_Aladdin;
	D3DXVECTOR3 startPosition;
};
