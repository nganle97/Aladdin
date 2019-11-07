#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerHangThrowingState.h"
#include "PlayerThrowingState.h"
#include "PlayerHangingState.h"
#include "PlayerClimbingState.h"
#include "../../GameDefines/define.h"

PlayerHangThrowingState::PlayerHangThrowingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex = 3;
}

PlayerHangThrowingState::PlayerHangThrowingState(PlayerData* playerData,Entity* rope)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	Rope = rope;
	this->RopeType = rope->Tag;
	if (mPlayerData->player->getFaceDirection() == Entity::FaceDirection::LEFT)
		mPlayerData->player->SetReverse(false);
	else mPlayerData->player->SetReverse(true);

}


PlayerHangThrowingState::~PlayerHangThrowingState()
{

}


void PlayerHangThrowingState::Update(float dt)
{
	//mPlayerData->player->GetCurrentAnimation()->Update(dt);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 5 && canThrow == true)
	{
		mPlayerData->player->ThrowApple();
		isDone = true;
		canThrow = false;
	}
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		if (this->RopeType==Entity::HorizontalRope)
		this->mPlayerData->player->SetState(new PlayerHangingState(this->mPlayerData,Rope));
		else 	this->mPlayerData->player->SetState(new PlayerClimbingState(this->mPlayerData, Rope));

		return;
	}
}


void PlayerHangThrowingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

	switch (side)
	{
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		this->mPlayerData->player->SetState(new PlayerStandingState(mPlayerData));

		return;

	default:
		break;
	}
}

void PlayerHangThrowingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(false);
	}
	else if (keys[VK_RIGHT])
		mPlayerData->player->SetReverse(true);
}

PlayerState::StateName PlayerHangThrowingState::GetState()
{
	return PlayerState::HangThrow;
}