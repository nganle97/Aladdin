#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerCuttingState.h"
#include "PlayerThrowingState.h"
#include "PlayerJumpingState.h"
#include "PlayerClimbJumpingState.h"
#include "PlayerStoppingState.h"
#include "PlayerJumpThrowingState.h"
#include "PlayerMoveJumpingState.h"
#include "PlayerUpCuttingState.h"
#include "PlayerJumpCuttingState.h"
#include "PlayerFlippingState.h"
#include "PlayerClimbingState.h"
#include "PlayerHangingState.h"
#include "PlayerSwingingState.h"
#include "PlayerHangCuttingState.h"
#include "PlayerFallingState.h"
#include "PlayerHangThrowingState.h"
#include "PlayerDownCuttingState.h"
#include "PlayerDownThrowingState.h"
#include "PlayerHitState.h"
#include "PlayerDyingState.h"
#include "../Weapon/Fire.h"

Player::Player()
{

	this->Tag = Entity::Aladdin;
	numApples = 10;
	this->HP = 11;
	mAnimationHanging = new Animation(eID::ALADDIN, "hang", 5, 0.45f, NULL);
	this->mPlayerData = new PlayerData();
	this->mPlayerData->player = this;
	this->vx = 0;
	this->vy = 0;
	faceDirection = FaceDirection::RIGHT;
	mCurrentAnimation = new Animation();
	this->SetState(new PlayerStandingState(this->mPlayerData));
	Lives = 3;
	Score = 0;
	Money = 0;

}

Player::~Player()
{
}

void Player::Update(float dt)
{
	if (mPlayerData->player->getState() != PlayerState::Climb&&mPlayerData->player->getState() != PlayerState::Hang)
		mCurrentAnimation->Update(dt);
	if (this->mPlayerData->state)
	{

		this->mPlayerData->state->Update(dt);
	}

	Entity::Update(dt);

	timeCreateFire -= dt;
	timeChangeStateStair -= dt;
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (this->mPlayerData->state)
	{
		this->mPlayerData->state->HandleKeyboard(keys);
	}
}

void Player::OnKeyPressed(int key)
{
#pragma region JUMP=0x43_CUT=0x58_THROW=0x5A
	if (key == 0x43)
	{
		if (allowJump)
		{
			if (mCurrentState == PlayerState::Stand || mCurrentState == PlayerState::Up || mCurrentState == PlayerState::Down || mCurrentState == PlayerState::Throw || mCurrentState == PlayerState::Cut || mCurrentState == PlayerState::Hit)
			{
				this->SetState(new PlayerJumpingState(this->mPlayerData));
			}
			else
				if (mCurrentState == PlayerState::Run)
				{
					this->SetState(new PlayerMoveJumpingState(this->mPlayerData));
				}
				else if (mCurrentState == PlayerState::Climb)
				{
					this->SetState(new PlayerClimbJumpingState(this->mPlayerData));
				}

			allowJump = false;
		}
	}
	else
		if (key == 0x58)
		{
			if (allowCut)
			{

				if (mCurrentState == PlayerState::Stand || mCurrentState == PlayerState::Throw || mCurrentState == PlayerState::Hit)
				{
					this->SetState(new PlayerCuttingState(this->mPlayerData));
				}
				else
					if (mCurrentState == PlayerState::Jump || mCurrentState == PlayerState::MoveJump || mCurrentState == PlayerState::ClimbJump || mCurrentState == PlayerState::Fall || mCurrentState == PlayerState::Flippe || mCurrentState == PlayerState::JumpThrow)
					{
						this->SetState(new PlayerJumpCuttingState(this->mPlayerData));

					}
					else
						if (mCurrentState == PlayerState::Up)
						{
							this->SetState(new PlayerUpCuttingState(this->mPlayerData));
						}
						else if (mCurrentState == PlayerState::Down)
						{

							this->SetState(new PlayerDownCuttingState(this->mPlayerData));

						}
				if (this->mCurrentState != PlayerState::Hang&&this->mCurrentState != PlayerState::Climb) allowCut = false;

				//Entity* tmp = new class JafarWeapon(D3DXVECTOR2(posX + 200, posY -100), this);
				//this->mGameMap->GetListWeapons()->push_back(tmp);

			}

		}
		else
			if (key == 0x5A)
			{
				if (allowThrow&&numApples>0)
				{

					if (mCurrentState == PlayerState::Jump || mCurrentState == PlayerState::MoveJump || mCurrentState == PlayerState::Fall || mCurrentState == PlayerState::Flippe || mCurrentState == PlayerState::ClimbJump || mCurrentState == PlayerState::JumpCut)
					{
						this->SetState(new PlayerJumpThrowingState(this->mPlayerData));
					}
					else if (mCurrentState == PlayerState::Stand || mCurrentState == PlayerState::Cut || mCurrentState == PlayerState::Hit)
					{
						this->SetState(new PlayerThrowingState(this->mPlayerData));
					}
					else if (mCurrentState == PlayerState::Hang || mCurrentState == PlayerState::Climb)
					{
					}
					else if (mCurrentState == PlayerState::Down)
					{
						this->SetState(new PlayerDownThrowingState(this->mPlayerData));
					}
					allowThrow = false;
				}
			}
#pragma endregion


	//Face direction
	if (key == VK_LEFT)
	{
		this->faceDirection = Entity::FaceDirection::LEFT;
	}
	else if (key == VK_RIGHT)
	{
		faceDirection = Entity::FaceDirection::RIGHT;
	}
}

void Player::OnKeyUp(int key)
{
	if (key == 0x43)
		allowJump = true;
	else
		if (key == 0x58)
			allowCut = true;
		else
			if (key == 0x5A)
				allowThrow = true;
}

void Player::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->SetFlipHorizontal(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());

	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		if (!(mCurrentAnimation->mCurrentIndex%2==0&&timeImmortal>0))
			mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
	{
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
	}
}

void Player::SetState(PlayerState *newState)
{
	delete this->mPlayerData->state;
	timeNoCollisionBottom = 0;
	this->mPlayerData->state = newState;
	this->changeAnimation(newState->GetState());
	mCurrentState = newState->GetState();

}

void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	//khi đang chết thì không xét va chạm
	if (mPlayerData->player->getState() == PlayerState::Die || mPlayerData->player->getState() == PlayerState::Revive)
		return;
	if (impactor->IsDestroy() == true) return;
	switch (impactor->Tag)
	{
	case (Entity::VerticalRope):
	{
		Entity::CollisionReturn tmp = GameCollision::RecteAndRect(GetBoundVerticalRope(), impactor->GetBound());
		if (tmp.IsCollided)
		{

			if (mPlayerData->player->getState() != PlayerState::Climb&&mPlayerData->player->GetVy() > 0)
			{
				mPlayerData->player->SetPosition(impactor->GetPosition().x, this->posY);
				if (mPlayerData->player->GetBound().top < impactor->GetBound().top)
				{
					mPlayerData->player->AddPosition(0, impactor->GetBound().top - mPlayerData->player->GetBound().top);
				}
				mPlayerData->player->SetState(new PlayerClimbingState(mPlayerData, impactor));
			}
		}
		break;
	}

	case (Entity::HorizontalRope):
	{
		Entity::CollisionReturn tmp = GameCollision::RecteAndRect(GetBoundHorizontalRope(), impactor->GetBound());
		if (tmp.IsCollided)
		{

			if (mPlayerData->player->getState() != PlayerState::Hang&&mPlayerData->player->GetVy() > 0)
			{
				mPlayerData->player->SetVy(0);
				mPlayerData->player->AddPosition(0, mAnimationHanging->GetSprite()->GetHeight() - mPlayerData->player->GetCurrentAnimation()->GetSprite()->GetHeight() - 1);
				mPlayerData->player->SetState(new PlayerHangingState(mPlayerData, impactor));
			}
		}
		break;
	}
	case (Entity::Items):
		if (impactor->ItemTag == Entity::ItemTypes::Apple)
			this->numApples++;
		else if (impactor->ItemTag == Entity::ItemTypes::RestartPoint)
			this->RevivePoint = D3DXVECTOR2(impactor->GetPosition().x, impactor->GetBound().bottom);
		else if (impactor->ItemTag == Entity::ItemTypes::ExtraHealth)
		{
			HP = min(11, HP + 2);
		}
		else if (impactor->ItemTag == Entity::ItemTypes::MagicLamp)
		{
			RECT region;
			region.left = impactor->GetPosition().x - 150;
			region.right = impactor->GetPosition().x + 150;
			region.top = impactor->GetPosition().y - 100;
			region.bottom = impactor->GetPosition().y + 100;
			mGameMap->ClearEnemiesInRegion(region);
		}
		else if (impactor->ItemTag == Entity::ItemTypes::OneUP)
		{
			Lives++;
		}
		else if (impactor->ItemTag == Entity::ItemTypes::SpendThese)
		{
			Money++;
		}

		break;
	case (Entity::SpringBoard):
	{
		//	Entity::CollisionReturn tmp = GameCollision::RecteAndRect(GetBoundVerticalRope(), impactor->GetBound());
		//if (tmp.IsCollided)
		{
			if (mPlayerData->player->GetVy() >= 0 && this->GetPosition().y >= impactor->GetBound().top) mPlayerData->player->SetState(new PlayerFlippingState(mPlayerData));
		}
	}
	break;
	case (Entity::ChangeEnableStair):
	{
		if (timeChangeStateStair <= 0)
		{
			timeChangeStateStair = 5;
			mPlayerData->player->EnableStair1 = !(mPlayerData->player->EnableStair1);
			mPlayerData->player->EnableStair2 = !(mPlayerData->player->EnableStair1);
		}
		break;
	}
	case (Entity::Stair1):
	{
		if (mPlayerData->player->EnableStair1) this->mPlayerData->state->OnCollision(impactor, side, data);
		break;
	}
	case (Entity::Stair2):
	{
		if (mPlayerData->player->EnableStair2) this->mPlayerData->state->OnCollision(impactor, side, data);
		break;
	}

	case (Entity::Fire):
		if (this->timeCreateFire <= 0&&this->vy>=0)
		{
			RECT AladdinWithFire;
			AladdinWithFire.bottom = posY;
			AladdinWithFire.top = posY - 20;
			int PosX = posX;;
			if (this->GetCurrentAnimation()->GetAnchorPoint().x != -1) PosX = this->GetCurrentAnimation()->GetAnchorPoint().x;
			AladdinWithFire.left = PosX - 15;
			AladdinWithFire.right = PosX + 15;
			if (GameCollision::isCollide(impactor->GetBound(), AladdinWithFire) == true)
			{
				Sound::getInstance()->play("FireFromCoal", false, 1);
				this->timeCreateFire = 0.6;
				Entity * tmp;
				tmp = new class Fire(D3DXVECTOR2(posX, posY));
				this->mGameMap->InsertWeapon(tmp);
			}
		}
		break;

	case Entity::EnemiesWeapon:
	case Entity::Flame:
	case Entity::JafarWeapon1:
	case Entity::JafarWeapon2:
		if (GameCollision::isCollide(this->GetBoundBody(),impactor->GetBound()) == false && impactor->Tag != JafarWeapon2) return;
		if (this->timeImmortal <= 0 && impactor->Tag != JafarWeapon1)
		{
			if (impactor->Tag != Flame)
			{
				Entity::TakeDamage(1);
				Sound::getInstance()->play("AladdinHurt", false, 1);
				SetTimeImmortal(1.8);
			}
			else
				if (timeCreateFire<0.4)
				{
					Entity::TakeDamage(1);
					Sound::getInstance()->play("AladdinHurt", false, 1);
					SetTimeImmortal(1.8);
				}
			if (this->HP <= 0)
			{
				SceneManager::GetInstance()->GetCurrentScene()->StopMusic();
				Sound::getInstance()->play("AladdinDie", false, 1);
				Lives--;
				this->mPlayerData->player->SetState(new PlayerDyingState(mPlayerData));
				return;
			}
			PlayerState::StateName tmp = this->mPlayerData->player->getState();
			if (tmp == PlayerState::Stand)
			{
				this->mPlayerData->player->SetState(new PlayerHitState(mPlayerData));
			}
		}

		break;
	case Entity::EntityTypes::Camel:
		if (vy > 0)
		{
			impactor->SetDestroy(true);
			if (vx == 0)
			{
				this->SetState(new PlayerJumpingState(mPlayerData));
			}
			else this->SetState(new PlayerMoveJumpingState(mPlayerData));
			Sound::getInstance()->play("CamelSpit", false, 1);
		}
		break;
	default:
		this->mPlayerData->state->OnCollision(impactor, side, data);
	}
}

void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data)
{

	this->mPlayerData->state->OnCollision(impactor, data);
}

RECT Player::GetBound()
{
	POINT tmp = this->mPlayerData->player->GetCurrentAnimation()->GetAnchorPoint();
	RECT rect;
	if (tmp.x == -1 && tmp.y == -1)
	{
		rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 2;
		rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
		rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight();
		rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight();
	}
	else
	{
		if (this->mCurrentReverse == false)
		{
			rect.left = this->posX - tmp.x;
			rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
		}
		else
		{
			rect.right = this->posX + tmp.x;
			rect.left = rect.right - mCurrentAnimation->GetSprite()->GetWidth();
		}
		rect.top = this->posY - tmp.y;
		rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight();
	}

	return rect;
}

RECT Player::GetBoundVerticalRope()
{
	RECT rect;

	rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 4;
	rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth() / 2;
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight() * 3 / 4;
	rect.bottom = rect.top + mCurrentAnimation->GetSprite()->GetHeight() / 2;
	return rect;
}

RECT Player::GetBoundHorizontalRope()
{
	RECT rect;

	rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 4;
	rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth() / 2;
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight();
	rect.bottom = rect.top + 1;
	return rect;
}

RECT Player::GetBoundBody()
{
	RECT rect;
	rect.left = this->posX - 18;
	rect.right = this->posX + 18;
	rect.top = this->posY - min(48,mCurrentAnimation->GetSprite()->GetHeight());
	rect.bottom = this->posY;

	return rect;
}

RECT Player::GetBoundWeapon()
{
	RECT rect = this->GetBound();;
	if (faceDirection == FaceDirection::RIGHT)
	{
		rect.left += this->mCurrentAnimation->GetSprite()->GetWidth() / 2;
	}
	else
	{
		rect.right -= this->mCurrentAnimation->GetSprite()->GetWidth() / 2;
	}
	return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
	switch (state)
	{
	case PlayerState::Run:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "run", 13, 0.1f, NULL);
		break;

	case PlayerState::Stand:
		delete mCurrentAnimation;
		//mCurrentAnimation = new Animation(eID::ALADDIN, "stand", 39, 0.25f, NULL);
		mCurrentAnimation = new Animation(eID::ALADDIN, "stand", 39, 0.25f, NULL);
		break;

	case PlayerState::Up:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "up", 3, 0.2f, NULL);
		mCurrentAnimation->SetStop(true);
		break;

	case PlayerState::Down:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "down", 3, 0.2f, NULL);
		mCurrentAnimation->SetStop(true);
		break;

	case PlayerState::Cut:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "cut", 5, 0.1f, NULL);//0.15f
																			  //mCurrentAnimation = new Animation(eID::GUARDS, "Guard3rdThrow", 5, 1.0f, NULL);
		break;

	case PlayerState::Throw:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "throw", 6, 0.09f, NULL);//0.1f
		break;

	case PlayerState::Jump:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "jump", 10, 0.3f, NULL);
		break;

	case PlayerState::Fall:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "fall", 2, 0.25f, NULL);
		mCurrentAnimation->SetStop(true);
		timeNoCollisionBottom = 0;
		break;

	case PlayerState::Stop:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "stop", 9, 0.15f, NULL);
		break;

	case PlayerState::JumpThrow:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "jumpthrow", 7, 0.15f, NULL);//0.15f
		mCurrentAnimation->SetStop(true);
		break;
	case PlayerState::MoveJump:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "movejump", 9, 0.28f, NULL);
		mCurrentAnimation->SetStop(true);
		break;
	case PlayerState::JumpCut:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "jumpcut", 8, 0.15f, NULL);
		mCurrentAnimation->SetStop(true);
		break;
	case PlayerState::Land:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "land", 12, 0.1f, NULL);
		break;
	case PlayerState::DownCut:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "downcut", 7, 0.15f, NULL);//0.15f

		break;
	case PlayerState::DownThrow:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "downthrow", 5, 0.1f, NULL);
		break;
	case PlayerState::UpCut:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "upcut", 21, 0.15f, NULL);//0.15f
		break;
	case PlayerState::Flippe:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "flippe", 14, 0.15f, NULL);
		break;
	case PlayerState::Climb:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "climb", 10, 0.15f, NULL);
		break;
	case PlayerState::Hang:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "hang", 5, 0.45f, NULL);
		mCurrentAnimation->SetStop(true);
		break;
	case PlayerState::Swing:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "swing", 10, 0.15f, NULL);
		break;
	case PlayerState::HangCut:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "hangcut", 7, 0.15f, NULL);//0.15f
		break;
	case PlayerState::HangThrow:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "hangthrow", 5, 0.1f, NULL);//0.1f
		break;
	case PlayerState::Push:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "push", 9, 0.15f, NULL);
		break;
	case PlayerState::ClimbJump:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "climbjump", 9, 0.15f, NULL);
		break;
	case PlayerState::Hit:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "hit", 6, 0.15f, NULL);
		break;
	case PlayerState::Die:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "die", 28, 0.25f, NULL);
		break;
	case PlayerState::Revive:
		delete mCurrentAnimation;
		mCurrentAnimation = new Animation(eID::ALADDIN, "revive", 10, 0.2f, NULL);
		break;
	}


	this->width = mCurrentAnimation->GetSprite()->GetWidth();
	this->height = mCurrentAnimation->GetSprite()->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
	if (this->vx > 0)
	{
		return MoveDirection::MoveToRight;
	}
	else if (this->vx < 0)
	{
		return MoveDirection::MoveToLeft;
	}

	return MoveDirection::None;
}

Player::FaceDirection Player::getFaceDirection()
{
	return faceDirection;
}


void Player::OnNoCollisionWithBottom(float dt)
{
	//Các trạng thái đang leo dây dọc hoặc dây ngang thì sẽ không xét NoCollision Bottom
	if (mCurrentState == PlayerState::Climb || mCurrentState == PlayerState::Hang || mCurrentState == PlayerState::HangThrow || mCurrentState == PlayerState::HangCut || mCurrentState == PlayerState::ClimbJump || mCurrentState == PlayerState::Swing)
	{
		return;
	}

	//Nếu Player đang rơi thì trì hoãn thời gian Fall 
	if (mPlayerData->player->GetVy() >= 0)
		mPlayerData->player->timeNoCollisionBottom += dt;

	//Nếu thời gian rơi >2 giây thì chuyển Player sang trạng thái Falling.
	if (mPlayerData->player->timeNoCollisionBottom > 2 && mPlayerData->player->GetVx() != 0) mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
	if (mCurrentState != PlayerState::Climb&&mCurrentState != PlayerState::Fall&&mCurrentState != PlayerState::Jump&&mCurrentState != PlayerState::MoveJump&&mCurrentState != PlayerState::JumpCut&&mCurrentState != PlayerState::JumpThrow&&mCurrentState != PlayerState::Flippe
		&&mCurrentState != PlayerState::Cut&&mCurrentState != PlayerState::DownCut&&mCurrentState != PlayerState::UpCut
		)
	{
		if (mPlayerData->player->timeNoCollisionBottom > 1 && mPlayerData->player->GetVx() != 0) mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
		mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	}
}

PlayerState::StateName Player::getState()
{
	return mCurrentState;
}



Animation* Player::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

void Player::SetCamera(Camera *camera)
{
	this->mCamera = camera;
}


void Player::SetGameMap(GameMap *gamemap)
{
	this->mGameMap = gamemap;
}

GameMap* Player::getGameMap()
{
	return this->mGameMap;
}

void Player::ThrowApple()
{
	if (numApples < 0) return;
	class Apple *tmp;
	numApples--;
	switch (mCurrentState)
	{
	case PlayerState::HangThrow:
		if (this->getFaceDirection() == Entity::FaceDirection::LEFT)
			tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().left + 9, mPlayerData->player->GetBound().top + 46));
		else
			tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().right - 9, mPlayerData->player->GetBound().top + 46));
		break;
	case PlayerState::DownThrow:
		if (this->getFaceDirection() == Entity::FaceDirection::LEFT)
			tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().left - 9, mPlayerData->player->GetBound().top + 16));
		else
			tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().right - 9, mPlayerData->player->GetBound().top + 16));
		break;
	case PlayerState::JumpThrow:
		if (this->getFaceDirection() == Entity::FaceDirection::LEFT)
			tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().left + 6, mPlayerData->player->GetBound().top + 14));
		else
			tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().right - 6, mPlayerData->player->GetBound().top + 14));
		break;
	case PlayerState::Throw:
		if (this->getFaceDirection() == Entity::FaceDirection::LEFT)
			tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().left + 11, mPlayerData->player->GetBound().top + 11));
		else
			tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().right - 11, mPlayerData->player->GetBound().top + 11));
		break;
	default:
		tmp = new class Apple(D3DXVECTOR2(mPlayerData->player->GetBound().right, mPlayerData->player->GetBound().top + 40));
	}
	if (mPlayerData->player->getFaceDirection() == Entity::FaceDirection::LEFT)
		tmp->SetVx(-190.0f);
	else tmp->SetVx(190.0f);
	tmp->SetVy(0.98f);
	Sound::getInstance()->play("ThrowApple", false, 1);
	mPlayerData->player->getGameMap()->InsertAppleAladdin(tmp);
}

int Player::GetNumApples()
{
	return numApples;
}
bool Player::IsAllowCut()
{
	return allowCut;
}
void Player::SetAllowCut(bool flag)
{
	allowCut = flag;
}
void Player::TakeDamage(int Damage)
{
	if (timeImmortal > 0) return;
	Entity::TakeDamage(Damage);
	Sound::getInstance()->play("AladdinHurt", false, 1);
	SetTimeImmortal(1.8);
	if (this->HP <= 0)
	{
		SceneManager::GetInstance()->GetCurrentScene()->StopMusic();
		Sound::getInstance()->play("AladdinDie", false, 1);
		Lives--;
		this->mPlayerData->player->SetState(new PlayerDyingState(mPlayerData));
		return;
	}
	PlayerState::StateName tmp = this->getState();
	if (tmp == PlayerState::Stand)
		this->mPlayerData->player->SetState(new PlayerHitState(mPlayerData));
}

void Player::SetRevivePoint(D3DXVECTOR2 revivePoint)
{
	this->RevivePoint = revivePoint;
}

void Player::SetStartPoint(D3DXVECTOR2 startPoint)
{
	this->StartPoint = startPoint;
}


D3DXVECTOR2 Player::GetRevivePoint()
{
	return this->RevivePoint;
}

D3DXVECTOR2 Player::GetStartPoint()
{
	return this->StartPoint;
}

int Player::GetNumLives()
{
	return Lives;
}

void Player::SetLives(int live)
{
	Lives = live;;
}

int Player::GetNumScore()
{
	return Score;
}

void Player::SetScore(int score)
{
	Score = score;;
}

int Player::GetNumMoney()
{
	return Money;
}

void Player::SetMoney(int money)
{
	Money = money;;
}