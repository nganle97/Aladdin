#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameGlobal.h"
#include "../../../GameObjects/Entity.h"
#include "../../../GameComponents/GameCollision.h"
#include "CivilianEnemy4thState.h"
#include "CivilianEnemy4thData.h"
#include "CivilianEnemy4thBeatState.h"
#include "CivilianEnemy4thRunState.h"
#include "CivilianEnemy4thStandState.h"
#include "../../Player/Player.h"



class CivilianEnemy4th :public Entity
{
public:

	CivilianEnemy4th();
	CivilianEnemy4th(D3DXVECTOR2 position, Player* mplayer);
	~CivilianEnemy4th();

	Player *mPlayer;

	void Update(float dt);

	void SetState(CivilianEnemy4thState *newState);

	virtual CivilianEnemy4thState::StateName CivilianEnemy4th::GetState();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(71, 33, 222));
	virtual void Draw(D3DXVECTOR2 transform);

	virtual RECT GetBound();
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Animation *GetCurrentAnimation();

	Animation *GetAnimation(CivilianEnemy4thState::StateName state);

	void SetReverse(bool flag);

	bool IsNearToPlayer();

	bool IsInAttackRange();

	int minX, maxX;
	float Vx;
protected:
	
	bool mCurrentReverse = false;
	void OnSetPosition(D3DXVECTOR3 poks);

	CivilianEnemy4thData *mCivilianEnemy4thData;

	Animation	*mCurrentAnimation,
				*mAnimationStand,
				*mAnimationBeat,
				*mAnimationRun;
		

	void changeAnimation(CivilianEnemy4thState::StateName state);

	CivilianEnemy4thState::StateName mCurrentState;


};
