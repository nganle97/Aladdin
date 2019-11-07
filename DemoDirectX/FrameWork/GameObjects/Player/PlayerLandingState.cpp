#include "PlayerLandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerUpState.h"
#include "PlayerDownState.h"
#include "PlayerCuttingState.h"
#include "PlayerThrowingState.h"
#include "../../GameDefines/define.h"

PlayerLandingState::PlayerLandingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerLandingState::~PlayerLandingState()
{

}

void PlayerLandingState::Update(float dt)
{
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 6) isDone = true;
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerLandingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}


}

void PlayerLandingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag != Entity::EntityTypes::SpringBoard)
	switch (side)
	{
	case Entity::Bottom:
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		return;

	default:
		break;
	}
}

PlayerState::StateName PlayerLandingState::GetState()
{
	return PlayerState::Land;
}