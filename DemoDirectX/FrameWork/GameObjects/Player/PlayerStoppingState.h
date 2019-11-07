#pragma once
#include "PlayerState.h"

class PlayerStoppingState :public PlayerState
{
public:
	PlayerStoppingState(PlayerData* playerData);
	~PlayerStoppingState();

	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
};