#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerHangCuttingState.h"
#include "PlayerThrowingState.h"
#include "PlayerHangingState.h"
#include "PlayerClimbingState.h"
#include "../../GameDefines/define.h"

PlayerHangCuttingState::PlayerHangCuttingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}
PlayerHangCuttingState::PlayerHangCuttingState(PlayerData* playerData,Entity* rope)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	if (mPlayerData->player->getFaceDirection() == Entity::FaceDirection::LEFT)
		mPlayerData->player->SetReverse(false);
	else mPlayerData->player->SetReverse(true);
	Rope = rope;
}

PlayerHangCuttingState::~PlayerHangCuttingState()
{

}

void PlayerHangCuttingState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex >= 3 || this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex <=6)
		this->mPlayerData->player->SetMakeDamage(true);
	else
		this->mPlayerData->player->SetMakeDamage(false);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 7) isDone = true;
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		if (this->Rope->Tag == Entity::HorizontalRope)
		{
			Sound::getInstance()->play("AladdinCut", false, 1);
			this->mPlayerData->player->SetMakeDamage(false);
			this->mPlayerData->player->SetState(new PlayerHangingState(this->mPlayerData, Rope));
		}
		else
		{
			Sound::getInstance()->play("AladdinCut", false, 1);
			this->mPlayerData->player->SetMakeDamage(false);
			this->mPlayerData->player->SetState(new PlayerClimbingState(this->mPlayerData, Rope));
		}

		return;
	}
}


void PlayerHangCuttingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

void PlayerHangCuttingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(false);
	}
	else if (keys[VK_RIGHT])
		mPlayerData->player->SetReverse(true);
}

PlayerState::StateName PlayerHangCuttingState::GetState()
{
	return PlayerState::HangCut;
}