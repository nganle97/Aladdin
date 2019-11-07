#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerJumpThrowingState.h"
#include "PlayerThrowingState.h"
#include "PlayerFallingState.h"
#include "PlayerLandingState.h"
#include "../../GameDefines/define.h"

PlayerJumpThrowingState::PlayerJumpThrowingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	acceleratorX = Define::PLAYER_RUN_SPEED;
	acceleratorY = 10.0f / 6;
	if (mPlayerData->player->getFaceDirection() == Entity::FaceDirection::LEFT)
		mPlayerData->player->SetReverse(true);
	else mPlayerData->player->SetReverse(false);
	mPlayerData->player->SetVy(mPlayerData->player->GetVy());
	noPressed = false;
}

PlayerJumpThrowingState::~PlayerJumpThrowingState()
{

}

void PlayerJumpThrowingState::Update(float dt)
{
	/*if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 6) isDone = true;//

	
	Code kiểm tra chạm đất -> đổi State sang Standing.
	
	
	*/
	if (mPlayerData->player->GetVy() < Define::PLAYER_MAX_JUMP_VELOCITY)
		mPlayerData->player->AddVy(acceleratorY);
	//**/
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 4 && canThrow == true)
	{
		mPlayerData->player->ThrowApple();
		isDone = true;
		canThrow = false;
	}
	if (noPressed)
	{
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			//player dang di chuyen sang ben trai      
			mPlayerData->player->SetVx(0);
		}
		else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			//player dang di chuyen sang phai   
			mPlayerData->player->SetVx(0);
		}
	}
}


void PlayerJumpThrowingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

void PlayerJumpThrowingState::HandleKeyboard(std::map<int, bool> keys)
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

PlayerState::StateName PlayerJumpThrowingState::GetState()
{
	return PlayerState::JumpThrow;
}