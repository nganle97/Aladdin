#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameGlobal.h"
#include "../../../GameObjects/Entity.h"
#include "../../../GameComponents/GameCollision.h"
#include "CivilianEnemy2ndState.h"
#include "CivilianEnemy2ndData.h"
#include "CivilianEnemy2ndThrowState.h"
#include "../../Player/Player.h"


class GameMap;
class CivilianEnemy2nd :public Entity
{
public:

	CivilianEnemy2nd();
	CivilianEnemy2nd(D3DXVECTOR2 position, Player* mplayer);
	~CivilianEnemy2nd();

	Player *mPlayer;

	void SetGameMap(GameMap *gamemap);

	GameMap* getGameMap();

	void Update(float dt);

	void SetState(CivilianEnemy2ndState *newState);

	virtual CivilianEnemy2ndState::StateName CivilianEnemy2nd::GetState();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(71, 33, 222));
	virtual void Draw(D3DXVECTOR2 transform);

	virtual RECT GetBound();
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	Animation *GetCurrentAnimation();

	Animation *GetAnimation(CivilianEnemy2ndState::StateName state);

	void SetReverse(bool flag);

	bool IsNearToPlayer();

protected:
	bool mCurrentReverse = false;
	void OnSetPosition(D3DXVECTOR3 poks);

	GameMap *mGameMap;

	CivilianEnemy2ndData *mCivilianEnemy2ndData;

	Animation	*mCurrentAnimation,
				*mAnimationThrow;

	void changeAnimation(CivilianEnemy2ndState::StateName state);

	CivilianEnemy2ndState::StateName mCurrentState;


};
