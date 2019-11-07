#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerStoppingState.h"
#include "PlayerUpState.h"
#include "PlayerDownState.h"
#include "../../GameDefines/define.h"
#include "PlayerCuttingState.h"

PlayerStoppingState::PlayerStoppingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerStoppingState::~PlayerStoppingState()
{

}

void PlayerStoppingState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 9) isDone = true;
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerStoppingState::HandleKeyboard(std::map<int, bool> keys)
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


void PlayerStoppingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

	switch (side)
	{
	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

		this->mPlayerData->player->SetVy(0);

		return;
	}
	default:return;
	}
}
PlayerState::StateName PlayerStoppingState::GetState()
{
	return PlayerState::Stop;
}