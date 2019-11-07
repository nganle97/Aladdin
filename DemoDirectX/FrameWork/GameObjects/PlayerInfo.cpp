#include "PlayerInfo.h"
#include "../GameComponents/GameGlobal.h"


PlayerInfo::PlayerInfo()
{

}

PlayerInfo::~PlayerInfo()
{

}
PlayerInfo::PlayerInfo(Player* player)
{
	init(player);
}
bool PlayerInfo::init(Player* player)
{


	this->position = D3DXVECTOR3(0, 0, 0);

	this->player = player;
	playerHP = player->GetHealth();
	healthMeter = new Animation(eID::ITEMS, "Health" + to_string(playerHP) + "_", 4, 1.0f, NULL);
	this->Apple = new Animation(eID::ITEMS, "apple", 1, 1.0f, NULL);
	this->Money = new Animation(eID::ITEMS, "spendthese", 1, 1.0f, NULL);
	this->UP = new Animation(eID::ITEMS, "UP", 1, 1.0f, NULL);
	healthMeterPosition = D3DXVECTOR3(10, 20, 0);
	ApplePosition = D3DXVECTOR3(GameGlobal::GetWidth() / 2 - 20, GameGlobal::GetHeight() / 2 - 10, 0);
	MoneyPosition = D3DXVECTOR3(GameGlobal::GetWidth() / 2 - 40, GameGlobal::GetHeight() / 2 - 10, 0);
	UPPosition = D3DXVECTOR3(20, GameGlobal::GetHeight() / 2 - 10, 0);
	numScorePosition = D3DXVECTOR3(GameGlobal::GetWidth() - 47, 50, 0);
	numApplesPosition = D3DXVECTOR3(GameGlobal::GetWidth() - 7, GameGlobal::GetHeight()-5,0);
	numLivesPosition = D3DXVECTOR3( 80 ,GameGlobal::GetHeight() - 5, 1000);
	numMoneyPosition = D3DXVECTOR3(GameGlobal::GetWidth() - 47, GameGlobal::GetHeight() - 5, -1001);

	this->numApples = Text(to_wstring(this->player->GetNumApples()), 50, 50, FW_NORMAL, false, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255), L"Consolas");
	this->numLives = Text(to_wstring(this->player->GetNumLives()), 50, 50, FW_NORMAL, false, DT_LEFT, D3DCOLOR_XRGB(0, 0, 255), L"Consolas");
	this->numMoney = Text(to_wstring(this->player->GetNumMoney()), 50, 50, FW_NORMAL, false, DT_LEFT, D3DCOLOR_XRGB(255, 0, 0), L"Consolas");
	this->numScore = Text(to_wstring(this->player->GetNumScore()), 100, 100, FW_BOLD, false, DT_LEFT, D3DCOLOR_XRGB(255, 255, 0), L"Arial");
	return true;
}


void PlayerInfo::Update(float dt)
{
	if (playerHP != player->GetHealth())
	{
		playerHP = player->GetHealth();
		delete healthMeter;
		healthMeter = new Animation(eID::ITEMS, "Health" + to_string(playerHP) + "_", 4, 1.0f, NULL);
	}
	healthMeter->Update(dt);
	numApples.SetString(this->player->GetNumApples());
	numLives.SetString(this->player->GetNumLives());
	numMoney.SetString(this->player->GetNumMoney());
	numScore.SetString(this->player->GetNumScore());
}

void PlayerInfo::Draw()
{

	if (mCamera)
	{
		//D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		//	GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x + mCamera->GetBound().left + healthMeterPosition.x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y + mCamera->GetBound().top + healthMeterPosition.y);
		healthMeter->Draw(healthMeterPosition, RECT(), D3DXVECTOR2(), trans);

		trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x + mCamera->GetBound().left + this->ApplePosition.x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y + mCamera->GetBound().top + this->ApplePosition.y);
		this->Apple->Draw(this->ApplePosition, RECT(), D3DXVECTOR2(), trans);


		trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x + mCamera->GetBound().left + MoneyPosition.x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y + mCamera->GetBound().top + MoneyPosition.y);
		Money->Draw(MoneyPosition, RECT(), D3DXVECTOR2(), trans);


		trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x + mCamera->GetBound().left + UPPosition.x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y + mCamera->GetBound().top + UPPosition.y);
		UP->Draw(UPPosition, RECT(), D3DXVECTOR2(), trans);

		this->numApples.Draw(numApplesPosition);
		this->numLives.Draw(numLivesPosition);
		this->numMoney.Draw(numMoneyPosition);
		this->numScore.Draw(numScorePosition);
	}
	else
	{
		healthMeter->Draw();
		this->Apple->Draw();
	}
}


void PlayerInfo::SetCamera(Camera* camera)
{
	this->mCamera = camera;
}