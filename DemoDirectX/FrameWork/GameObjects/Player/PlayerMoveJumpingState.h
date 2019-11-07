#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerMoveJumpingState : public PlayerState
{
public:
	PlayerMoveJumpingState(PlayerData *playerData);
	~PlayerMoveJumpingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();

protected:
	int currentPosY;
	bool isLeftOrRightKeyPressed;
	bool isFalling = false;
	float acceleratorY;
	float acceleratorX;
	bool allowMoveRight, allowMoveLeft;
	bool isDone = false;

};

