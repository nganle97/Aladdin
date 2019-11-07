#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameGlobal.h"
#include "../../../GameObjects/Entity.h"
#include "../../../GameComponents/GameCollision.h"

#include "../../Player/Player.h"
#include "../../../GameComponents/GameMap.h"
#include "../Guard_3rd/Guard3State.h"

class GameMap;

class Guard3 :public Entity
{
public:
	Guard3();
	Guard3(D3DXVECTOR2 position, Player *player);
	~Guard3();

	Player *mPlayer;
	void SetGameMap(GameMap *gamemap);

	GameMap* getGameMap();

	void Update(float dt);

	void SetState(Guard3State *newState);

	virtual Guard3State::StateName Guard3::GetState();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(D3DXVECTOR2 transfrom);
		
	virtual RECT GetBound();
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Animation *GetCurrentAnimation();

	Animation *GetAnimation(Guard3State::StateName state);

	void SetReverse(bool flag);

	bool GetReverse();

	bool IsNearToPlayer();
	bool IsInAttackRange();

	bool IsInActiveRegion();

	void LimitDistance();

	int minX, maxX;
protected:

	int x;	// Toa do x luc khoi tao 
			// khoang gioi han di chuyen cua enemy


	bool mCurrentReverse = false;


	Guard3Data *mGuard3Data;

	GameMap *mGameMap;

	Animation	*mCurrentAnimation,
				*mAnimationDance,
				*mAnimationBeaten,
				*mAnimationRun,
				*mAnimationStand,
				*mAnimationThrow;

	void changeAnimation(Guard3State::StateName state);

	Guard3State::StateName mCurrentState;
};