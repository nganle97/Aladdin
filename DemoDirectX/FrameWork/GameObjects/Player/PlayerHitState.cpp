#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerHitState.h"
#include "PlayerUpState.h"
#include "PlayerDownState.h"
#include "../../GameDefines/define.h"
#include "PlayerCuttingState.h"

PlayerHitState::PlayerHitState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetMakeDamage(false);
}

PlayerHitState::~PlayerHitState()
{

}

void PlayerHitState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 6) isDone = true;
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerHitState::HandleKeyboard(std::map<int, bool> keys)
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


void PlayerHitState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
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
PlayerState::StateName PlayerHitState::GetState()
{
	return PlayerState::Hit;
}