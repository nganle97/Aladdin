#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameGlobal.h"
#include "../../../GameObjects/Entity.h"
#include "../../../GameComponents/GameCollision.h"
#include "Guard1State.h"
#include "Guard1Data.h"
#include "Guard1RunState.h"
#include "Guard1BeatState.h"
#include "../../Player/Player.h"


class Guard1 :public Entity
{
public:

	Guard1();
	Guard1(D3DXVECTOR2 position,Player* mplayer);
	~Guard1();

	Player *mPlayer;

	void Update(float dt);

	void SetState(Guard1State *newState);

	virtual Guard1State::StateName Guard1::GetState();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(71, 33, 222));
	virtual void Draw(D3DXVECTOR2 transform);
	
	virtual RECT GetBound();
	virtual RECT GetBoundBody();
	virtual RECT GetBoundWeapon();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Animation *GetCurrentAnimation();

	Animation *GetAnimation(Guard1State::StateName state);

	void SetReverse(bool flag);

	bool GetReverse();

	bool IsNearToPlayer();

	bool IsInAttackRange();

	bool IsInActiveRegion();

	float Vx;
protected:

	int x;	// Toa do x luc khoi tao 
			// khoang gioi han di chuyen cua enemy
	int minX, maxX;
	
	bool mCurrentReverse=false;
	void OnSetPosition(D3DXVECTOR3 poks);

	Guard1Data *mGuard1Data;

	Animation	*mCurrentAnimation,
				*mAnimationRun,
				*mAnimationBeat,
				*mAnimationBeaten;

	void changeAnimation(Guard1State::StateName state);

	Guard1State::StateName mCurrentState;


}; 
