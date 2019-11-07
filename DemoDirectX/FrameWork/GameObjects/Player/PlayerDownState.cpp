#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerDownState.h"
#include "PlayerDownCuttingState.h"
#include "PlayerDownThrowingState.h"
#include "../../GameDefines/define.h"

PlayerDownState::PlayerDownState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}



PlayerDownState::~PlayerDownState()
{

}

void PlayerDownState::Update(float dt)
{

}


void PlayerDownState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

void PlayerDownState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_DOWN])
	{
		if (keys[VK_LEFT])
		{
			mPlayerData->player->SetReverse(true);
			return;
		}
		else if (keys[VK_RIGHT])
		{
			mPlayerData->player->SetReverse(false);
			return;
		}
	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

PlayerState::StateName PlayerDownState::GetState()
{
	return PlayerState::Down;
}