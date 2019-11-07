#include "PlayerMoveJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/define.h"

PlayerMoveJumpingState::PlayerMoveJumpingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceleratorX = Define::PLAYER_RUN_SPEED;
	acceleratorY = 10.0f / 6;   //Tỉ lệ 1:12 so với PlayerMAX_JUMP_VELOCITY  chia  số frame
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	currentPosY = this->mPlayerData->player->GetPosition().y;
}


PlayerMoveJumpingState::~PlayerMoveJumpingState()
{

}

void PlayerMoveJumpingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);
}


void PlayerMoveJumpingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:

			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

			this->mPlayerData->player->SetVx(0);
		break;

	case Entity::Right:	
		
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);

			this->mPlayerData->player->SetVx(0);
		break;
	case Entity::Top:

			return;
	
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (mPlayerData->player->GetVy()>0)
		{
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			break;
		}
	default:
		break;
	}

}

void PlayerMoveJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		isLeftOrRightKeyPressed = true;
		//di chuyen sang phai
		mPlayerData->player->SetVx(Define::PLAYER_RUN_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		isLeftOrRightKeyPressed = true;
		//di chuyen sang trai
		mPlayerData->player->SetVx(-Define::PLAYER_RUN_SPEED);
	}
	else
	{
		isLeftOrRightKeyPressed = false;
	}
}


PlayerState::StateName PlayerMoveJumpingState::GetState()
{
	return PlayerState::MoveJump;
}
