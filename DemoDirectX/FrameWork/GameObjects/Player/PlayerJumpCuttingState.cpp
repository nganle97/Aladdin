#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerJumpCuttingState.h"
#include "PlayerThrowingState.h"
#include "PlayerFallingState.h"
#include "PlayerLandingState.h"
#include "../../GameDefines/define.h"

PlayerJumpCuttingState::PlayerJumpCuttingState(PlayerData* playerData)
{
	
	this->mPlayerData = playerData;
	acceleratorX = Define::PLAYER_RUN_SPEED;
	acceleratorY = 10.0f / 6;
	mPlayerData->player->SetVy(mPlayerData->player->GetVy());
	noPressed = false;
}
PlayerJumpCuttingState::PlayerJumpCuttingState(PlayerData* playerData,int posY)
{

	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	acceleratorX = Define::PLAYER_RUN_SPEED;
	acceleratorY = 10.0f / 6;
	mPlayerData->player->SetVy(mPlayerData->player->GetVy());
	currentPosY = posY;
	noPressed = false;
}


PlayerJumpCuttingState::~PlayerJumpCuttingState()
{

}

void PlayerJumpCuttingState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 5)
	{
		this->mPlayerData->player->SetMakeDamage(true);
		Sound::getInstance()->play("AladdinCut", false, 1);
	}
	else
		this->mPlayerData->player->SetMakeDamage(false);

	if (mPlayerData->player->GetVy() < Define::PLAYER_MAX_JUMP_VELOCITY)
		mPlayerData->player->AddVy(acceleratorY);
	else mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 6) isDone = true;
	if (mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetMakeDamage(false);
		mPlayerData->player->SetState(new PlayerStandingState(mPlayerData));
	}
}
void PlayerJumpCuttingState::HandleKeyboard(std::map<int, bool> keys)
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


void PlayerJumpCuttingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

PlayerState::StateName PlayerJumpCuttingState::GetState()
{
	return PlayerState::JumpCut;
}