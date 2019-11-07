#pragma once
#include "PlayerState.h"

class PlayerJumpCuttingState :public PlayerState
{
public:
	PlayerJumpCuttingState(PlayerData* playerData);
	PlayerJumpCuttingState(PlayerData* playerData,int posY);

	~PlayerJumpCuttingState();

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
};