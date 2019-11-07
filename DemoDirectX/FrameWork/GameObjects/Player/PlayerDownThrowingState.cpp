#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerDownState.h"
#include "PlayerDownThrowingState.h"
#include "PlayerThrowingState.h"
#include "../../GameDefines/define.h"

PlayerDownThrowingState::PlayerDownThrowingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerDownThrowingState::~PlayerDownThrowingState()
{

}

void PlayerDownThrowingState::Update(float dt)
{
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 4&&canThrow==true)
	{
		mPlayerData->player->ThrowApple();
		isDone = true;
		canThrow = false;
	}
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetState(new PlayerDownState(this->mPlayerData));
		return;
	}
}


void PlayerDownThrowingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

	switch (side)
	{
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));


		return;

	default:
		break;
	}
}

void PlayerDownThrowingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);
	}
	else if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);
	}
}

PlayerState::StateName PlayerDownThrowingState::GetState()
{
	return PlayerState::DownThrow;
}