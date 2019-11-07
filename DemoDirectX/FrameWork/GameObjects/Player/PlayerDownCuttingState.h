#pragma once
#include "PlayerState.h"

class PlayerDownCuttingState :public PlayerState
{
public:
	PlayerDownCuttingState(PlayerData* playerData);
	~PlayerDownCuttingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
};