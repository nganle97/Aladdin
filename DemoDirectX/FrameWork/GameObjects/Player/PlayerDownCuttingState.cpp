#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerDownState.h"
#include "PlayerDownCuttingState.h"
#include "PlayerThrowingState.h"
#include "../../GameDefines/define.h"

PlayerDownCuttingState::PlayerDownCuttingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerDownCuttingState::~PlayerDownCuttingState()
{

}

void PlayerDownCuttingState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex >= 3 || this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex <= 5)

	{
		this->mPlayerData->player->SetMakeDamage(true);
		if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex==4)	Sound::getInstance()->play("AladdinCutDown", false, 1);
	}
	else
		this->mPlayerData->player->SetMakeDamage(false);

	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 7) isDone = true;
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetMakeDamage(false);
		this->mPlayerData->player->SetState(new PlayerDownState(this->mPlayerData));
		return;
	}
}


void PlayerDownCuttingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

void PlayerDownCuttingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] )
	{
		mPlayerData->player->SetReverse(true);
	}
	else if(keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);
	}
}

PlayerState::StateName PlayerDownCuttingState::GetState()
{
	return PlayerState::DownCut;
}