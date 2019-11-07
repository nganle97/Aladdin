#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerDyingState.h"
#include "PlayerUpState.h"
#include "PlayerDownState.h"
#include "PlayerReviveState.h"
#include "../../GameDefines/define.h"
#include "PlayerCuttingState.h"

PlayerDyingState::PlayerDyingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetTimeImmortal(0);
}

PlayerDyingState::~PlayerDyingState()
{

}

void PlayerDyingState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == this->mPlayerData->player->GetCurrentAnimation()->mTotalFrame) isDone = true;
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetHealth(11);
		this->mPlayerData->player->getGameMap()->ReloadObjects();
		this->mPlayerData->player->getGameMap()->ReloadItems();
		this->mPlayerData->player->getGameMap()->GetListWeapons()->clear();
		this->mPlayerData->player->getGameMap()->GetListApples()->clear();
		if (this->mPlayerData->player->GetRevivePoint() != D3DXVECTOR2(-1, -1))
		{
			this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetRevivePoint());
			Sound::getInstance()->play("Revive", false, 1);
			this->mPlayerData->player->SetState(new PlayerReviveState(this->mPlayerData));
		}
		else
		{
			this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetStartPoint());
			SceneManager::GetInstance()->GetCurrentScene()->PlayMusic(); 
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
		return;
	}
}

void PlayerDyingState::HandleKeyboard(std::map<int, bool> keys)
{

}


void PlayerDyingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}
PlayerState::StateName PlayerDyingState::GetState()
{
	return PlayerState::Die;
}