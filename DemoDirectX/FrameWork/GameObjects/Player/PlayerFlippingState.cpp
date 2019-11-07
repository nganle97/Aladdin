#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerFlippingState.h"
#include "PlayerThrowingState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/define.h"

PlayerFlippingState::PlayerFlippingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY*2.5);
	acceleratorX = Define::PLAYER_RUN_SPEED;
	acceleratorY =10.0f / 6;
}

PlayerFlippingState::~PlayerFlippingState()
{

}

void PlayerFlippingState::Update(float dt)
{

		mPlayerData->player->AddVy(acceleratorY*2.3);

	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 14) isDone = true;
	if (mPlayerData->player->GetVy() == Define::PLAYER_MAX_JUMP_VELOCITY||(this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex==1&&isDone==true))
	{
		this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
		return;
	}
}


void PlayerFlippingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag != Entity::EntityTypes::SpringBoard)
	switch (side)
	{
	case Entity::Left:
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;

	case Entity::Right:
		if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;

	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		this->mPlayerData->player->SetVy(0);
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;

	default:
		break;
	}

}

void PlayerFlippingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		mPlayerData->player->SetVx(acceleratorX);

	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang trai
		mPlayerData->player->SetVx(-acceleratorX);

	}

}

PlayerState::StateName PlayerFlippingState::GetState()
{
	return PlayerState::Flippe;
}