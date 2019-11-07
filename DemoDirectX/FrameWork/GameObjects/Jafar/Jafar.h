#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameObjects/Entity.h"
#include "../../GameComponents/GameCollision.h"
#include "JafarState.h"
#include "JafarData.h"
#include "JafarOriginalState.h"
#include "JafarSnakeState.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameComponents/GameMap.h"
#include "../../Scenes/EndScene.h"


class GameMap;
class Jafar :public Entity
{
public:
	Jafar();
	Jafar(D3DXVECTOR2 position, Player *player);
	~Jafar();

	Player *mPlayer;

	void Update(float dt);

	void SetState(JafarState *newState);

	virtual JafarState::StateName Jafar::GetState();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(D3DXVECTOR2 transfrom);

	virtual RECT GetBound();

	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);

	Animation *GetCurrentAnimation();

	Animation *GetAnimation(JafarState::StateName state);

	void SetReverse(bool flag);

	bool GetReverse();

	bool IsInActiveRegion();

protected:
	bool mCurrentReverse = false;


	JafarData *mJafarData;

	GameMap *mGameMap;

	Animation	*mCurrentAnimation,
				*mAnimationOriginal,
				*mAnimationSnake;

	void changeAnimation(JafarState::StateName state);

	JafarState::StateName mCurrentState;
};