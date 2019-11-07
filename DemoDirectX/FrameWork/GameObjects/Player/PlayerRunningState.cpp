#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerStoppingState.h"
#include "PlayerUpState.h"
#include "PlayerRunCuttingState.h"
#include "PlayerPushingState.h"
#include "../../GameDefines/define.h"


PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	mPlayerData->player->SetVy(0);
	x = this->mPlayerData->player->GetPosition().x;
	acceleratorX = 8.0f;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float dt)
{
	if (mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 13)
		mPlayerData->player->GetCurrentAnimation()->SetLoop(true, 3, 12);

}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		mPlayerData->player->SetVx(Define::PLAYER_RUN_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang trai
		mPlayerData->player->SetVx(-Define::PLAYER_RUN_SPEED);
	}
	else
	{
		if (this->mPlayerData->player->GetPosition().x-x > 150||this->mPlayerData->player->GetPosition().x - x <- 150)//trị tuyệt đối
			this->mPlayerData->player->SetState(new PlayerStoppingState(this->mPlayerData));
		else this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	if (impactor->Tag != Entity::EntityTypes::SpringBoard)
	switch (side)
	{
	case Entity::Left:
	{
		//va cham phia ben trai player
		if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			this->mPlayerData->player->allowMoveLeft = false;

			//day Player ra phia ben phai de cho player khong bi xuyen qua object
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

			//this->mPlayerData->player->SetState(new PlayerPushingState(this->mPlayerData));
		}

		return;
	}

	case Entity::Right:
	{
		//va cham phia ben phai player
		if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->mPlayerData->player->allowMoveRight = false;
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			//this->mPlayerData->player->SetState(new PlayerPushingState(this->mPlayerData));
		}
		return;
	}

	case Entity::Top:
		break;
	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= Define::PLAYER_BOTTOM_RANGE_FALLING)
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		return;

	default:
		break;
	
	}
}

PlayerState::StateName PlayerRunningState::GetState()
{
	return PlayerState::Run;
}

void PlayerRunningState::SetXPoint(int x)
{
	this->x = x;
}