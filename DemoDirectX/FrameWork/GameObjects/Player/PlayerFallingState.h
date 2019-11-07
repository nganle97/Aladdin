#pragma once
#include "PlayerState.h"


class PlayerFallingState : public PlayerState
{
public:
	PlayerFallingState(PlayerData *playerData);
	~PlayerFallingState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);


	virtual StateName GetState();

protected:
	float acceleratorY;
	float acceleratorX;

	bool allowMoveX;

	bool isLeftOrRightKeyPressed;
};

