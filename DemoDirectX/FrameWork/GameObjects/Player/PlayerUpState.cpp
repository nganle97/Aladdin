#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerUpState.h"
#include "../../GameDefines/define.h"

PlayerUpState::PlayerUpState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerUpState::~PlayerUpState()
{

}

void PlayerUpState::Update(float dt)
{
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);

}


void PlayerUpState ::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Bottom:
	case Entity::BottomLeft:
	case Entity::BottomRight:
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		return;

	default:
		break;
	}

}

void PlayerUpState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_UP])
	{
		if (keys[VK_LEFT])
		{
			mPlayerData->player->SetReverse(true);
			return;
		}
		else if (keys[VK_RIGHT])
		{
			mPlayerData->player->SetReverse(false);
		}
	}
		else
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));	
		return;
	}
}


PlayerState::StateName PlayerUpState::GetState()
{
	return PlayerState::Up;
}