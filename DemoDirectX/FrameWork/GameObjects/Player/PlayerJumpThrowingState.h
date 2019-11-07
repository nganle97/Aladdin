#pragma once
#include "PlayerState.h"

class PlayerJumpThrowingState :public PlayerState
{
public:
	PlayerJumpThrowingState(PlayerData* playerData);
	~PlayerJumpThrowingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);


	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	int currentPosY;

	bool isFalling = false;
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;
	bool isDone = false;
	bool canThrow = true;
};