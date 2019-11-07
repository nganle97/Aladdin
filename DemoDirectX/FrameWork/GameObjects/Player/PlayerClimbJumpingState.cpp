#include "PlayerClimbJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerClimbingState.h"
#include "../../GameDefines/define.h"

PlayerClimbJumpingState::PlayerClimbJumpingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceleratorX = Define::PLAYER_RUN_SPEED;
	acceleratorY = 10.0f / 6;   //Tỉ lệ 1:12 so với PlayerMAX_JUMP_VELOCITY  chia  số frame
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY-20.0f);
	currentPosY = this->mPlayerData->player->GetPosition().y;
	noPressed = false;
}


PlayerClimbJumpingState::~PlayerClimbJumpingState()
{

}

void PlayerClimbJumpingState::Update(float dt)
{
	if (mPlayerData->player->GetVy() < Define::PLAYER_MAX_JUMP_VELOCITY)
		mPlayerData->player->AddVy(acceleratorY);
	fallingTime += dt;
	if (noPressed)
		mPlayerData->player->SetVx(0);
	if (fallingTime > 2.0f)
	{
		mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
	}

}


void PlayerClimbJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		mPlayerData->player->SetVx(acceleratorX);

		noPressed = false;
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang trai
		mPlayerData->player->SetVx(-acceleratorX);

		noPressed = false;
	}
	else
	{
		noPressed = true;
	}
}



void PlayerClimbJumpingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
		//
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
		if (impactor->Tag == Entity::HorizontalRope)
			return;
		if (this->mPlayerData->player->GetVy()<0)
		{
			this->mPlayerData->player->AddPosition(0, +(data.RegionCollision.bottom - data.RegionCollision.top));
			{
				this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

			}
		}
		return;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:

		if (mPlayerData->player->GetVy()>0)
		{
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			break;
		}
	default:
		break;
	}

	
}
PlayerState::StateName PlayerClimbJumpingState::GetState()
{
	return PlayerState::ClimbJump;
}
