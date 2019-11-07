#include "PlayerClimbingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerUpState.h"
#include "PlayerDownState.h"
#include "PlayerCuttingState.h"
#include "PlayerFallingState.h"
#include "PlayerThrowingState.h"
#include "PlayerHangThrowingState.h"
#include "PlayerHangCuttingState.h"
#include "../../GameDefines/define.h"

PlayerClimbingState::PlayerClimbingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}
PlayerClimbingState::PlayerClimbingState(PlayerData* playerData,Entity* VerticalRope)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	verticalRope = VerticalRope;
	if (mPlayerData->player->getFaceDirection() == Entity::FaceDirection::LEFT)
		mPlayerData->player->SetReverse(false);
	else mPlayerData->player->SetReverse(true);
}

PlayerClimbingState::~PlayerClimbingState()
{

}

void PlayerClimbingState::Update(float dt)
{
	Entity::CollisionReturn tmp1 = GameCollision::RecteAndRect(mPlayerData->player->GetBoundVerticalRope(), verticalRope->GetBound());
	if (!tmp1.IsCollided)
	{
		mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
		return;
	}
	Animation* tmp = mPlayerData->player->GetCurrentAnimation();;

	if (typeUpdate == 1)
	{
		tmp->Update(dt);
		typeUpdate = 0;
	}
	else if (typeUpdate == -1)
	{
		tmp->Update(dt,true);
		typeUpdate = 0;
	}
	else return;
	/*if (tmp->mCurrentIndex > tmp->mTotalFrame) tmp->mCurrentIndex = 1;
	else if (tmp->mCurrentIndex > tmp->mTotalFrame < 0) tmp->mCurrentIndex = tmp->mTotalFrame;
	RECT mRect = SpriteManager::getInstance()->getSourceRect(eID::ALADDIN, "climb" + to_string(tmp->mCurrentIndex) + ".bmp");
	tmp->GetSprite()->SetWidth(mRect.right - mRect.left);
	tmp->GetSprite()->SetHeight(mRect.bottom - mRect.top);
	tmp->GetSprite()->SetSourceRect(mRect);*/
}

void PlayerClimbingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Top:

	{
		this->mPlayerData->player->AddPosition(0, +(data.RegionCollision.bottom - data.RegionCollision.top));
	default:
		break;
	}

}
return;
}

void PlayerClimbingState::HandleKeyboard(std::map<int, bool> keys)
{
	
	if (keys[VK_UP])
	{
		typeUpdate = 1;
		if (mPlayerData->player->GetBound().top < verticalRope->GetBound().top)
		{
			mPlayerData->player->AddPosition(0, 0.75f);
			return;
		}
		else
		{
			mPlayerData->player->AddPosition(0, -0.75f);
		}
	}
	else if (keys[VK_DOWN])
	{
		typeUpdate = -1;

		mPlayerData->player->AddPosition(0, 0.75f);
	}
	else if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);
	}
	else if (keys[0x5A])
	{
		if (mPlayerData->player->GetNumApples()>0)
		mPlayerData->player->SetState(new PlayerHangThrowingState(this->mPlayerData, verticalRope));
	}
	else if (keys[0x58])
	{
		if (mPlayerData->player->IsAllowCut() == true)
		{
			this->mPlayerData->player->SetAllowCut(false);
			mPlayerData->player->SetState(new PlayerHangCuttingState(this->mPlayerData, verticalRope));
		}
	}
}

PlayerState::StateName PlayerClimbingState::GetState()
{
	return PlayerState::Climb;
}