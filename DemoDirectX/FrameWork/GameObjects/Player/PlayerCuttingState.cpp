#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerCuttingState.h"
#include "PlayerThrowingState.h"
#include "../../GameDefines/define.h"

PlayerCuttingState::PlayerCuttingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex = 3;
}

PlayerCuttingState::~PlayerCuttingState()
{

}

void PlayerCuttingState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 4 || this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 3)

	{
		Sound::getInstance()->play("AladdinCut", false, 1);
		this->mPlayerData->player->SetMakeDamage(true);
	}
	else
		this->mPlayerData->player->SetMakeDamage(false);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 5) isDone = true;
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetMakeDamage(false);
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}


void PlayerCuttingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Bottom:
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		return;

	default:
		break;
	}
}

void PlayerCuttingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetMakeDamage(false);
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

PlayerState::StateName PlayerCuttingState::GetState()
{
	return PlayerState::Cut;
}