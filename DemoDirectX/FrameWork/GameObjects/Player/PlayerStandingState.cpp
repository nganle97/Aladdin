#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerUpState.h"
#include "PlayerDownState.h"
#include "PlayerCuttingState.h"
#include "PlayerThrowingState.h"
#include "../../GameDefines/define.h"

PlayerStandingState::PlayerStandingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerStandingState::~PlayerStandingState()
{

}

void PlayerStandingState::Update(float dt)
{
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);
}


void PlayerStandingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag!=Entity::EntityTypes::SpringBoard)
	switch (side)
	{
	case Entity::Bottom:
	case Entity::BottomLeft:
	case Entity::BottomRight:
		if (data.RegionCollision.right - data.RegionCollision.left >= Define::PLAYER_BOTTOM_RANGE_FALLING)
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		return;

	default:
		break;
	}

}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
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
PlayerState::StateName PlayerStandingState::GetState()
{
	return PlayerState::Stand;
}