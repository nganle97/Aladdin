#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	PlayerJumpingState(PlayerData *playerData);
	~PlayerJumpingState();

	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();

protected:
	int currentPosY;

	bool isFalling=false;
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;
	bool isDone = false;

};

