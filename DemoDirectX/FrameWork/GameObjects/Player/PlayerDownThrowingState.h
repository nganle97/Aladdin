#pragma once
#include "PlayerState.h"

class PlayerDownThrowingState :public PlayerState
{
public:
	PlayerDownThrowingState(PlayerData* playerData);
	~PlayerDownThrowingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
	bool canThrow = true;
};