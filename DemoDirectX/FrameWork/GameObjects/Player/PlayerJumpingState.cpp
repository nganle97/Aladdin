#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerClimbingState.h"
#include "../../GameDefines/define.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceleratorX =Define::PLAYER_RUN_SPEED;
	acceleratorY = 10.0f/6;   //Tỉ lệ 1:12 so với PlayerMAX_JUMP_VELOCITY  chia  số frame
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	currentPosY = this->mPlayerData->player->GetPosition().y;
	noPressed = false;
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);
}


void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
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



void PlayerJumpingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);


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
		/*if (this->mPlayerData->player->GetVy()<0)
		{
			this->mPlayerData->player->AddPosition(0, +(data.RegionCollision.bottom - data.RegionCollision.top));
			{
				this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

			}
		}*/
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
PlayerState::StateName PlayerJumpingState::GetState()
{
	return PlayerState::Jump;
}
