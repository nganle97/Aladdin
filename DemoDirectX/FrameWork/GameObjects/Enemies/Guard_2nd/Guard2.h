#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameGlobal.h"
#include "../../../GameObjects/Entity.h"
#include "../../../GameComponents/GameCollision.h"
#include "Guard2State.h"
#include "Guard2Data.h"
#include "Guard2ArouseState.h"
#include "Guard2BeatenState.h"
#include "Guard2BurnedState.h"
#include "Guard2CutState.h"
#include "Guard2DartState.h"
#include "Guard2RunState.h"
#include "../../Player/Player.h"



class Guard2 :public Entity
{
public:

	Guard2();
	Guard2(D3DXVECTOR2 position,Player* mplayer);

	~Guard2();

	Player *mPlayer;

	void Update(float dt);

	void SetState(Guard2State *newState);

	virtual Guard2State::StateName Guard2::GetState();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(71, 33, 222));
	virtual void Draw(D3DXVECTOR2 transform);

	virtual RECT GetBound();
	virtual RECT GetBoundBody();
	virtual RECT GetBoundWeapon();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Animation *GetCurrentAnimation();

	Animation *GetAnimation(Guard2State::StateName state);

	void SetReverse(bool flag);

	bool GetReverse();

	bool IsNearToPlayer();
	void LimitDistance();
	bool IsInActiveRegion();
	bool IsInAttackRange();

	float Vx;
	int minX, maxX;
protected:

	int x;	// Toa do x luc khoi tao 
			// khoang gioi han di chuyen cua enemy
	

	bool mCurrentReverse = false;
	void OnSetPosition(D3DXVECTOR3 poks);

	Guard2Data *mGuard2Data;

	Animation	*mCurrentAnimation,
				*mAnimationArouse,
				*mAnimationBeaten,
				*mAnimationBurned,
				*mAnimationCut,
				*mAnimationDart,
				*mAnimationRun;

	void changeAnimation(Guard2State::StateName state);

	Guard2State::StateName mCurrentState;


};
