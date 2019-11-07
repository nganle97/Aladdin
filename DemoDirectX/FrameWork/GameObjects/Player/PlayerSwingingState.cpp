#include "PlayerSwingingState.h"
#include "PlayerRunCuttingState.h"
#include "PlayerHangingState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/define.h"


PlayerSwingingState::PlayerSwingingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	acceleratorX = 8.0f;
}
PlayerSwingingState::PlayerSwingingState(PlayerData *playerData,Entity* HorizontalRope)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	acceleratorX = 8.0f;
	horizontalRope = HorizontalRope;

}


PlayerSwingingState::~PlayerSwingingState()
{
}

void PlayerSwingingState::Update(float dt)
{
	float tmp = mPlayerData->player->GetPosition().x;
	if (mPlayerData->player->GetBound().left < horizontalRope->GetBound().left || tmp>horizontalRope->GetBound().right)
	{
		mPlayerData->player->AddPosition(0, 5); //Khoảng cách đủ để GetBoundHorizontalRope không va chạm với Dây Ngang.
		mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
	}
}


void PlayerSwingingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{


}

void PlayerSwingingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang phai
		mPlayerData->player->SetVx(Define::PLAYER_RUN_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang trai
		mPlayerData->player->SetVx(-Define::PLAYER_RUN_SPEED);
	}
	else 
	{
		mPlayerData->player->SetState(new PlayerHangingState(mPlayerData,horizontalRope));
		return;
	}
}

PlayerState::StateName PlayerSwingingState::GetState()
{
	return PlayerState::Swing;
}
