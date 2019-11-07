#pragma once
#include "PlayerState.h"

class PlayerUpCuttingState :public PlayerState
{
public:
	PlayerUpCuttingState(PlayerData* playerData);
	~PlayerUpCuttingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
};