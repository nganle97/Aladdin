#pragma once

#include "../GameComponents/Animation.h"
#include "Entity.h"
//vien gach
#include "Player\Player.h"
#include "../GameComponents/Text.h"

class PlayerInfo
{
public:


	~PlayerInfo();
	PlayerInfo();
	PlayerInfo(Player* player);

	void Draw();
	void Update(float dt);

	void SetCamera(Camera* camera);

protected:
	bool init(Player* player);
	int playerHP;
	Animation *healthMeter;
	D3DXVECTOR3 healthMeterPosition;

	Animation *Apple;
	D3DXVECTOR3 ApplePosition;

	Animation *Money;
	D3DXVECTOR3 MoneyPosition;

	Animation *UP;
	D3DXVECTOR3 UPPosition;

	Text numApples;
	D3DXVECTOR3 numApplesPosition;

	Text numLives;
	D3DXVECTOR3 numLivesPosition;

	Text numMoney;
	D3DXVECTOR3 numMoneyPosition;

	Text numScore;
	D3DXVECTOR3 numScorePosition;

	Player* player;
	Camera *mCamera;
	D3DXVECTOR3 position;
};
