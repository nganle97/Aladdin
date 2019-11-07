#include "PlayerHangingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerUpState.h"
#include "PlayerDownState.h"
#include "PlayerCuttingState.h"
#include "PlayerThrowingState.h"
#include "PlayerSwingingState.h"
#include "PlayerClimbingState.h"
#include "PlayerHangCuttingState.h"
#include "PlayerHangThrowingState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/define.h"

PlayerHangingState::PlayerHangingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	if (this->mPlayerData->player->getFaceDirection() == Player::FaceDirection::RIGHT)
		this->mPlayerData->player->SetReverse(true);
	else  this->mPlayerData->player->SetReverse(false);
}
PlayerHangingState::PlayerHangingState(PlayerData* playerData,Entity* HorizontalRope)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	horizontalRope = HorizontalRope;
	if (this->mPlayerData->player->getFaceDirection() == Player::FaceDirection::RIGHT)
		this->mPlayerData->player->SetReverse(true);
	else  this->mPlayerData->player->SetReverse(false);
}

PlayerHangingState::~PlayerHangingState()
{

}

void PlayerHangingState::Update(float dt)
{
	Entity::CollisionReturn tmp = GameCollision::RecteAndRect(mPlayerData->player->GetBoundHorizontalRope(), horizontalRope->GetBound());
	if (!tmp.IsCollided)
	{
		mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
		return;
	}

	if (typeUpdate == false)
	{
		mPlayerData->player->GetCurrentAnimation()->Update(dt, true);
		if (mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1)
			typeUpdate = true;
	}
	else
	{
		mPlayerData->player->GetCurrentAnimation()->Update(dt);
		if (mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == mPlayerData->player->GetCurrentAnimation()->mTotalFrame)
			typeUpdate = false;
	}
}


void PlayerHangingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{


}

void PlayerHangingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT]||keys[VK_RIGHT])
	{		
		mPlayerData->player->SetState(new PlayerSwingingState(this->mPlayerData,horizontalRope));
	}
	else if (keys[0x58])
	{
		if (mPlayerData->player->IsAllowCut() == true)
		{
			this->mPlayerData->player->SetAllowCut(false);
			mPlayerData->player->SetState(new PlayerHangCuttingState(this->mPlayerData, horizontalRope));
		}
	}
	else if (keys[0x5A])
	{
		if (mPlayerData->player->GetNumApples()>0)
		mPlayerData->player->SetState(new PlayerHangThrowingState(this->mPlayerData, horizontalRope));
	}
	else if (keys[0x43])
	{
		mPlayerData->player->AddPosition(0, 5); //Khoảng cách đủ để GetBoundHorizontalRope không va chạm với Dây Ngang.
	}
}

PlayerState::StateName PlayerHangingState::GetState()
{
	return PlayerState::Hang;
}
Entity* PlayerHangingState::GetHorizontalRope()
{
	return horizontalRope;
}