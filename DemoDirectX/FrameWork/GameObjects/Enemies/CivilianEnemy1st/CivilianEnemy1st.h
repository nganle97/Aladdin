#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameGlobal.h"
#include "../../../GameObjects/Entity.h"
#include "../../../GameComponents/GameCollision.h"
#include "CivilianEnemy1stState.h"
#include "CivilianEnemy1stData.h"
#include "CivilianEnemy1stThrowState.h"
#include "../../Player/Player.h"


class GameMap;
class CivilianEnemy1st :public Entity
{
public:

	CivilianEnemy1st();
	CivilianEnemy1st(D3DXVECTOR2 position, Player* mplayer);
	~CivilianEnemy1st();

	Player *mPlayer;

	void SetGameMap(GameMap *gamemap);

	GameMap* getGameMap();

	void Update(float dt);

	void SetState(CivilianEnemy1stState *newState);

	virtual CivilianEnemy1stState::StateName CivilianEnemy1st::GetState();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(71, 33, 222));
	virtual void Draw(D3DXVECTOR2 transform);
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	virtual RECT GetBound();

	Animation *GetCurrentAnimation();

	Animation *GetAnimation(CivilianEnemy1stState::StateName state);

	bool IsNearToPlayer();

protected:

	void OnSetPosition(D3DXVECTOR3 poks);

	CivilianEnemy1stData *mCivilianEnemy1stData;

	GameMap *mGameMap;

	Animation	*mCurrentAnimation,
				*mAnimationThrow;

	void changeAnimation(CivilianEnemy1stState::StateName state);

	CivilianEnemy1stState::StateName mCurrentState;

	bool isNear = false;
};
