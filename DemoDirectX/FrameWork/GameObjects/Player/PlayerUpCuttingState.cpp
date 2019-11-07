#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerUpState.h"

#include "PlayerDownState.h"
#include "PlayerUpCuttingState.h"
#include "PlayerThrowingState.h"
#include "../../GameDefines/define.h"

PlayerUpCuttingState::PlayerUpCuttingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerUpCuttingState::~PlayerUpCuttingState()
{

}

void PlayerUpCuttingState::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 3 || this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 7
		|| this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 11 || this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 15
		|| this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 19)

	{
		this->mPlayerData->player->SetMakeDamage(true);
		Sound::getInstance()->play("AladdinCut", false, 1);
	}
	else

		this->mPlayerData->player->SetMakeDamage(false);


	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 21) isDone = true;
	if (this->mPlayerData->player->GetCurrentAnimation()->mCurrentIndex == 1 && isDone == true)
	{
		this->mPlayerData->player->SetMakeDamage(false);
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}


void PlayerUpCuttingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{


}
void PlayerUpCuttingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetMakeDamage(false);
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	else
			if (keys[VK_DOWN])
			{
				this->mPlayerData->player->SetMakeDamage(false);
				this->mPlayerData->player->SetState(new PlayerDownState(this->mPlayerData));
				return;
			}
}

PlayerState::StateName PlayerUpCuttingState::GetState()
{
	return PlayerState::UpCut;
}