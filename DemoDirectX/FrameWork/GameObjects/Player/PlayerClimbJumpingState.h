#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClimbJumpingState : public PlayerState
{
public:
	PlayerClimbJumpingState(PlayerData *playerData);
	~PlayerClimbJumpingState();

	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();

protected:
	int currentPosY;

	float fallingTime = 0;
	bool isFalling = false;
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;
	bool isDone = false;

};

