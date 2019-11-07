#pragma once
#include "PlayerData.h"
#include "../Entity.h"
#include <map>

class PlayerState
{
public:
	enum StateName
	{
		Climb,
		HangCut,
		ClimbJump,
		ClimbStand,
		HangThrow,
		Swing,
		Crazy,
		Cut,
		Dance,
		Die,
		Died,
		Down,
		DownThrow,
		DownCut,
		RunThrow,
		Flippe,
		Hug,
		Revive,
		Jump,
		Fall,
		JumpCut,
		JumpThrow,
		Land,
		MoveJump,
		Push,
		Run,
		RunCut,
		Stand,
		Stop,
		Hang,
		Throw,
		Up,
		UpCut,
		Hit
	};
	
	~PlayerState();

	virtual void Update(float dt);

	//side va cham voi player
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data);

	virtual void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState() = 0;

protected:
	PlayerState(PlayerData *playerData);
	PlayerState();

	PlayerData * mPlayerData;
};