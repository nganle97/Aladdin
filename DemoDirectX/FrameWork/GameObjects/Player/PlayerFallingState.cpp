#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerLandingState.h"
#include "../../GameDefines/define.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceleratorX = Define::PLAYER_RUN_SPEED;
	acceleratorY = 10.0f / 6;
	this->mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (this->mPlayerData->player->getFaceDirection() == Player::FaceDirection::RIGHT)
		this->mPlayerData->player->SetReverse(false);
	else  this->mPlayerData->player->SetReverse(true);

	if (this->mPlayerData->player->GetVx() == 0)
	{
		allowMoveX = false;
	}
	else
	{
		allowMoveX = true;
	}
}



PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
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

void PlayerFallingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

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
		this->mPlayerData->player->AddPosition(0, (data.RegionCollision.bottom - data.RegionCollision.top));
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			Sound::getInstance()->play("AladdinLanding", false, 1);
			this->mPlayerData->player->SetState(new PlayerLandingState(this->mPlayerData));
		return;
		
	default:
		break;
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
	return PlayerState::Fall;
}
