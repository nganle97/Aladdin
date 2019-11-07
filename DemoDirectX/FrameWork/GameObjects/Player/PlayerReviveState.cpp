#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerReviveState.h"
#include "PlayerUpState.h"
#include "PlayerDownState.h"
#include "../../GameDefines/define.h"
#include "PlayerCuttingState.h"

PlayerReviveState::PlayerReviveState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerReviveState::~PlayerReviveState()
{

}

void PlayerReviveState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 6) isDone = true;

	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		SceneManager::GetInstance()->GetCurrentScene()->PlayMusic();
		return;
	}
}

void PlayerReviveState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	else
		if (keys[VK_UP])
		{
			this->mPlayerData->player->SetState(new PlayerUpState(this->mPlayerData));
			return;
		}
		else
			if (keys[VK_DOWN])
			{
				this->mPlayerData->player->SetState(new PlayerDownState(this->mPlayerData));
				return;
			}
}


void PlayerReviveState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}
PlayerState::StateName PlayerReviveState::GetState()
{
	return PlayerState::Revive;
}