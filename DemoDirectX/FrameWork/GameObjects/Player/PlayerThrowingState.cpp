#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerThrowingState.h"
#include "PlayerUpState.h"
#include "../../GameDefines/define.h"
#include "PlayerCuttingState.h"

PlayerThrowingState::PlayerThrowingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerThrowingState::~PlayerThrowingState()
{

}

void PlayerThrowingState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 4 && canThrow == true)
	{
		mPlayerData->player->ThrowApple();
		isDone = true;
		canThrow = false;
	}
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);
}


void PlayerThrowingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

void PlayerThrowingState::HandleKeyboard(std::map<int, bool> keys)
{

	if (keys[0x58])
	{
		this->mPlayerData->player->SetState(new PlayerCuttingState(this->mPlayerData));
		return;
	}
	else
	{
		if (keys[VK_LEFT] || keys[VK_RIGHT])
		{
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			return;
		}
		else if (keys[VK_UP])
		{
			this->mPlayerData->player->SetState(new PlayerUpState(this->mPlayerData));
			return;
		}
	}
}

PlayerState::StateName PlayerThrowingState::GetState()
{
	return PlayerState::Throw;
}